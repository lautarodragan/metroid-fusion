"""Lag frames and logic frames, measured from outside the game.

The main loop (``AgbMain``, src/agbmain.c) runs one *logic frame* per
iteration: it increments ``gFrameCounter8Bit``/``gFrameCounter16Bit`` near the
start, runs the game mode's handler, clears bit 0 of ``gVBlankRequestFlag``
and halts until the V-blank interrupt sets it again. When a logic frame takes
longer than one video frame (280,896 cycles), the V-blank it was meant to wait
for has already passed and the game waits for the next one: the screen shows
the same picture twice. Such an emulated frame, in which the frame counter
does not advance, is a *lag frame*.

``retro_run`` of the mGBA core ends when the video frame ends (start of
V-blank), before the V-blank interrupt is serviced. So, at the end of an
emulated frame:

* if bit 0 of ``gVBlankRequestFlag`` is clear, the game finished its logic
  frame and is halted, waiting for V-blank: a *logic-frame boundary*. The next
  emulated frame starts a new logic frame (the frame counter advances in it);
* if it is set, a logic frame is still running (it will lag).

:class:`LogicStepper` drives an emulator one logic frame at a time from
boundary to boundary. Input is read once per logic frame (``UpdateInput``,
right before the counter is incremented), so the keys set before a logic
frame are the keys that logic frame sees. Two builds that run the same logic
at different speeds (for example the original and an optimized build) can be
driven in lockstep this way and compared at every boundary, which a
frame-by-frame comparison cannot do once one of them lags.

The module only reads RAM through the symbols of the ROM's map file, so it
works with any build (and with the original ROM, given a map of a matching
build).
"""

from __future__ import annotations

from dataclasses import dataclass, field

FRAME_COUNTER = "gFrameCounter16Bit"
VBLANK_FLAG = "gVBlankRequestFlag"


class LagError(RuntimeError):
    pass


def frame_counter(emu) -> int:
    return emu.u16(FRAME_COUNTER)


def at_boundary(emu) -> bool:
    """The game finished its logic frame and waits for V-blank."""
    return not (emu.u16(VBLANK_FLAG) & 1)


def game_mode(emu) -> tuple[int, int]:
    """(``gMainGameMode``, ``gSubGameMode1``)."""
    return emu.s16("gMainGameMode"), emu.s16("gSubGameMode1")


@dataclass
class LagStats:
    """Lag over a run of logic frames."""
    logic_frames: int = 0
    emulated_frames: int = 0
    # lag frames per logic frame (index = logic frame number in the run)
    per_frame: list[int] = field(default_factory=list)

    @property
    def lag_frames(self) -> int:
        return self.emulated_frames - self.logic_frames

    @property
    def lagging_logic_frames(self) -> int:
        """Logic frames that took more than one emulated frame."""
        return sum(1 for n in self.per_frame if n)

    def add(self, lag: int) -> None:
        self.logic_frames += 1
        self.emulated_frames += 1 + lag
        self.per_frame.append(lag)

    def summary(self) -> str:
        pct = 100.0 * self.lag_frames / self.emulated_frames if self.emulated_frames else 0.0
        return (f"{self.logic_frames} logic frames in {self.emulated_frames} emulated frames: "
                f"{self.lag_frames} lag frames ({pct:.1f}%), "
                f"{self.lagging_logic_frames} logic frames lagged")


class LogicStepper:
    """Run an emulator one logic frame at a time (see the module docstring)."""

    def __init__(self, emu, max_lag: int = 600):
        self.emu = emu
        self.max_lag = max_lag

    def sync(self) -> int:
        """Run until a logic-frame boundary; returns the emulated frames run."""
        n = 0
        while not at_boundary(self.emu):
            if n >= self.max_lag:
                raise LagError(f"no logic-frame boundary after {n} frames")
            self.emu.run(1)
            n += 1
        return n

    def step(self, keys=None) -> int:
        """Run one logic frame with ``keys`` held; returns its lag frames.

        Should start at a boundary (call :meth:`sync` once first); ends at
        the next one. If the frame counter does not advance in the first
        emulated frame (the game is not in its main loop yet, e.g. right
        after power-on, or waits for something else), the frames until it
        advances are counted as lag of this logic frame.
        """
        emu = self.emu
        if keys is not None:
            emu.set_input(keys)
        before = frame_counter(emu)
        emu.run(1)
        lag = 0
        while frame_counter(emu) == before:
            if lag >= self.max_lag:
                raise LagError(f"the frame counter did not advance in {lag} frames")
            emu.run(1)
            lag += 1
        while not at_boundary(emu):
            if lag >= self.max_lag:
                raise LagError(f"logic frame still running after {lag} lag frames")
            emu.run(1)
            lag += 1
        return lag

    def run(self, count: int, keys=None, stats: LagStats | None = None) -> LagStats:
        """Run ``count`` logic frames holding ``keys``."""
        stats = stats if stats is not None else LagStats()
        for _ in range(count):
            stats.add(self.step(keys))
        return stats


def count_lag_frames(emu, frames: int, keys=None) -> LagStats:
    """Run ``frames`` emulated frames and count those in which the frame
    counter did not advance (the plain definition, no boundary needed)."""
    stats = LagStats()
    if keys is not None:
        emu.set_input(keys)
    prev = frame_counter(emu)
    lag = None
    for _ in range(frames):
        emu.run(1)
        cur = frame_counter(emu)
        if cur != prev:
            if lag is not None:
                stats.add(lag)
            lag = 0
        elif lag is not None:
            lag += 1
        prev = cur
    if lag is not None:
        stats.add(lag)
    return stats


# ---------------------------------------------------------------------------
# PROFILE builds (make PROFILE=1, include/profile.h)
# ---------------------------------------------------------------------------

PROFILE_MAGIC = 0x464F5250
FRAME_CYCLES = 280896          # 228 lines of 1232 cycles
PROFILE_SPRITE_SLOTS = 24


def profile_regions(header=None) -> list[str]:
    """Names of ``enum ProfileRegion`` (include/profile.h), without ``PROF_``."""
    import re
    from pathlib import Path
    header = Path(header) if header else Path(__file__).resolve().parents[2] / "include" / "profile.h"
    text = header.read_text()
    body = text[text.index("enum ProfileRegion"):]
    body = body[body.index("{") + 1:body.index("};")]
    names = re.findall(r"^\s*PROF_(\w+)\s*,", body, re.M)
    return [n for n in names if n != "COUNT"]


class ProfileReader:
    """Reads ``gProfile.last`` (the counts of the last logic frame)."""

    def __init__(self, emu, header=None):
        self.emu = emu
        self.regions = profile_regions(header)
        if "gProfile" not in emu.symbols:
            raise LagError("not a PROFILE build (no gProfile in the map)")
        self.base = emu.symbols["gProfile"]
        n = len(self.regions)
        frame_words = n + 2 * PROFILE_SPRITE_SLOTS
        # struct Profile: magic, frames, isrCycles, loopStart, cur, last
        self.last = self.base + 16 + 4 * frame_words
        self.frame_words = frame_words

    def ok(self) -> bool:
        return self.emu.u32(self.base) == PROFILE_MAGIC

    def frames(self) -> int:
        return self.emu.u32(self.base + 4)

    def read(self) -> dict:
        import struct
        n = len(self.regions)
        words = struct.unpack(f"<{self.frame_words}I", self.emu.read(self.last, 4 * self.frame_words))
        return {
            "cycles": dict(zip(self.regions, words[:n])),
            "ai": list(words[n:n + PROFILE_SPRITE_SLOTS]),
            "draw": list(words[n + PROFILE_SPRITE_SLOTS:]),
        }
