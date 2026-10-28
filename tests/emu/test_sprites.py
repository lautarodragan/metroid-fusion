"""Samus, the HUD and projectiles are actually drawn (placeholder sprites).

Poses are checked on images rendered from OAM + OBJ VRAM + OBJ palettes
(oam_view.py), so they do not depend on the room's background or the
camera. References: tests/emu/reference/samus_<pose>.png, refreshed with
--update-references like the screenshots.
"""

from __future__ import annotations

import pytest

import harness
import oam_view
from test_screenshots import CHANNEL_TOLERANCE, MAX_DIFF_FRACTION, REFERENCE_DIR, diff_image

ARRIVAL_FRAMES = 200   # Samus is lowered from the gunship, facing the screen

# pose name -> input steps, from Samus standing still facing right
POSES = {
    "standing": [(2, "")],
    "running": [(12, "RIGHT")],
    "jumping": [(8, "A")],
    "spin_jump": [(6, "RIGHT"), (14, "A+RIGHT")],
    "aiming_up": [(10, "UP")],
    "aiming_diagonal": [(10, "L")],
    "crouching": [(10, "DOWN")],
    "shooting": [(2, "B"), (2, "")],
    "facing_left": [(12, "LEFT")],
}


@pytest.fixture(scope="module")
def standing_state(emu, boot):
    assert "in_game" in boot.states, "in-game state not reached"
    emu.load_state(boot.states["in_game"])
    emu.set_input([])
    emu.run(ARRIVAL_FRAMES)
    emu.run(10, "RIGHT")
    emu.run(40, [])
    return emu.save_state()


def do_pose(emu, state, pose):
    emu.load_state(state)
    for frames, keys in POSES[pose]:
        emu.run(frames, keys)
    return emu


def samus_sprites(emu, onscreen=False):
    return [s for s in oam_view.read_oam(emu, onscreen) if oam_view.is_samus(s)]


def test_samus_is_on_screen(emu, standing_state):
    """Samus has OAM entries and their pixels show up in the screenshot."""
    emu.load_state(standing_state)
    emu.run(1)
    sprites = samus_sprites(emu, onscreen=True)
    assert sprites, "no Samus sprites on screen"
    pals = oam_view.obj_palettes(emu)
    w, h, rgb = emu.screenshot()
    shown = 0
    total = 0
    for s in sprites:
        for x, y, c in oam_view.sprite_pixels(emu, s):
            if 0 <= x < w and 0 <= y < h:
                total += 1
                i = (y * w + x) * 3
                want = pals[s.palette][c]
                if all(abs(rgb[i + k] - want[k]) <= 8 for k in range(3)):
                    shown += 1
    assert total >= 150, f"Samus' sprites have only {total} opaque pixels on screen"
    # her feet may be behind the floor (BG1 has a higher priority than sprites)
    assert shown >= total * 0.6, f"only {shown} of {total} Samus pixels visible (covered by the background?)"


@pytest.mark.parametrize("pose", list(POSES))
def test_samus_pose(emu, standing_state, pose, pytestconfig, output_dir):
    do_pose(emu, standing_state, pose)
    w, h, rgb = oam_view.render(emu, samus_sprites(emu))
    ref = REFERENCE_DIR / f"samus_{pose}.png"
    if pytestconfig.getoption("--update-references"):
        harness.write_png(ref, w, h, rgb)
        return
    if not ref.exists():
        pytest.fail(f"no reference {ref}; create it with --update-references")
    rw, rh, ref_rgb = harness.read_png(ref)
    assert (rw, rh) == (w, h)
    frac = harness.image_diff(rgb, ref_rgb, CHANNEL_TOLERANCE)
    if frac > MAX_DIFF_FRACTION:
        output_dir.mkdir(parents=True, exist_ok=True)
        harness.write_png(output_dir / f"samus_{pose}.actual.png", w, h, rgb)
        harness.write_png(output_dir / f"samus_{pose}.diff.png", w, h, diff_image(rgb, ref_rgb))
        pytest.fail(f"samus_{pose}: {frac:.2%} of pixels differ from {ref.name}; see {output_dir}")


def test_poses_look_different(emu, standing_state):
    """Each pose gives its own picture (the art follows the animation)."""
    images = {}
    for pose in POSES:
        do_pose(emu, standing_state, pose)
        images[pose] = oam_view.render(emu, samus_sprites(emu))[2]
    distinct = {}
    for pose, img in images.items():
        distinct.setdefault(img, []).append(pose)
    same = [p for p in distinct.values() if len(p) > 1 and set(p) != {"standing", "shooting"}]
    assert not same, f"poses drawn identically: {same}"


def test_beam_is_drawn(emu, standing_state):
    """Shooting puts a beam sprite (OBJ palette 2, tile rows 4-5) on screen."""
    do_pose(emu, standing_state, "shooting")
    beams = [s for s in oam_view.read_oam(emu) if s.palette == 2 and 0x80 <= s.tile < 0xC0]
    assert beams, "no beam sprite after pressing B"
    assert sum(1 for s in beams for _ in oam_view.sprite_pixels(emu, s)) >= 10


def test_hud_is_drawn(emu, standing_state):
    """The energy counter sprites have visible (light) pixels."""
    emu.load_state(standing_state)
    emu.run(1)
    hud = [s for s in oam_view.read_oam(emu) if s.tile in (0x50, 0x54) and s.palette == 3]
    assert len(hud) == 2, "energy counter sprites missing"
    w, h, rgb = emu.screenshot()
    light = sum(1 for y in range(0, 20) for x in range(0, 64)
                if min(rgb[(y * w + x) * 3:(y * w + x) * 3 + 3]) > 200)
    assert light >= 40, f"energy counter almost blank ({light} light pixels)"
