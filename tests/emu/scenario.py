"""Scripted play-through of the open ROM: power on -> in-game.

The script uses fixed frame counts, so with a deterministic emulator every run
produces the same frames; screenshots are taken at named checkpoints.
`run_boot` records what happened (game mode transitions, checkpoints, save
states, PC sanity) for the tests to assert on.
"""

from __future__ import annotations

from dataclasses import dataclass, field

from harness import Emulator

# enum GameMode (include/globals.h)
GAME_MODE_TITLE = 0
GAME_MODE_IN_GAME = 1
GAME_MODE_MAP_SCREEN = 3
GAME_MODE_FILE_SELECT_OR_INTRO = 7

# gSubGameMode2 values used by AgbMain for GAME_MODE_TITLE / FILE_SELECT_OR_INTRO
TITLE_SUB_INTRO = 1
TITLE_SUB_TITLE_SCREEN = 4
FILE_SELECT_SUB_FILE_SELECT = 0
FILE_SELECT_SUB_NEW_FILE_INTRO = 1

# (frames, buttons, checkpoint name taken at the end of the step or None).
# "pulse:N" repeats N times: hold the buttons 2 frames, release 28.
BOOT_SCRIPT: list[tuple[str | int, str, str | None]] = [
    (200, "", "title_intro"),         # title intro (space view), idle
    (100, "", None),
    (5, "START", None),               # skip the intro
    (300, "", "title_screen"),
    (5, "START", None),               # -> file select
    (300, "", "file_select"),
    (5, "A", None),                   # pick file A ...
    (200, "", None),
    (5, "A", None),                   # ... start it ...
    (200, "", None),
    (5, "A", None),                   # ... confirm -> new file intro
    (400, "", "new_file_intro"),
    ("pulse:320", "A", None),         # page through the monologues
]
IN_GAME_SETTLE_FRAMES = 120           # after reaching GAME_MODE_IN_GAME
PC_CHECK_INTERVAL = 10


@dataclass
class BootRecord:
    transitions: list[tuple[int, tuple[int, int, int]]] = field(default_factory=list)
    screenshots: dict[str, tuple[int, int, bytes]] = field(default_factory=dict)
    states: dict[str, bytes] = field(default_factory=dict)
    bad_pc: list[tuple[int, str]] = field(default_factory=list)
    in_game_frame: int | None = None

    def modes(self) -> list[tuple[int, int, int]]:
        return [m for _, m in self.transitions]


def game_mode(emu: Emulator) -> tuple[int, int, int]:
    return (emu.s16("gMainGameMode"), emu.s16("gSubGameMode1"), emu.s16("gSubGameMode2"))


def _steps():
    for frames, buttons, checkpoint in BOOT_SCRIPT:
        keys = buttons.split("+") if buttons else []
        if isinstance(frames, str) and frames.startswith("pulse:"):
            for _ in range(int(frames[6:])):
                yield 2, keys, None
                yield 28, [], None
            if checkpoint:
                yield 0, [], checkpoint
        else:
            yield frames, keys, checkpoint


def run_boot(emu: Emulator) -> BootRecord:
    rec = BootRecord()
    prev = None

    def frame() -> None:
        nonlocal prev
        emu.run(1)
        m = game_mode(emu)
        if m != prev:
            rec.transitions.append((emu.frame_count, m))
            prev = m
        if emu.frame_count % PC_CHECK_INTERVAL == 0 and not emu.pc_is_sane():
            rec.bad_pc.append((emu.frame_count, emu.symbolize(emu.cpu_registers()["pc"])))

    for frames, keys, checkpoint in _steps():
        emu.set_input(keys)
        for _ in range(frames):
            frame()
            if prev[0] == GAME_MODE_IN_GAME and rec.in_game_frame is None:
                rec.in_game_frame = emu.frame_count
        if checkpoint:
            rec.screenshots[checkpoint] = emu.screenshot()
            rec.states[checkpoint] = emu.save_state()
        if rec.in_game_frame is not None:
            break
    emu.set_input([])
    if rec.in_game_frame is not None:
        for _ in range(IN_GAME_SETTLE_FRAMES):
            frame()
        rec.screenshots["in_game"] = emu.screenshot()
        rec.states["in_game"] = emu.save_state()
    return rec
