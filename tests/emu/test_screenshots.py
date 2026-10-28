"""Screenshot regression at the scenario checkpoints.

References live in tests/emu/reference/ and only show the open ROM's
placeholder art. Refresh them with `pytest tests/emu --update-references`
(or `tests/run_emu_tests.sh --update-references`) after an intended change,
look at the new images, and commit them.
"""

from __future__ import annotations

from pathlib import Path

import pytest

import harness

REFERENCE_DIR = Path(__file__).resolve().parent / "reference"
CHECKPOINTS = ["title_intro", "title_screen", "file_select", "new_file_intro", "in_game"]
# A pixel differs when one channel differs by more than CHANNEL_TOLERANCE;
# the test fails when more than MAX_DIFF_FRACTION of the pixels differ.
CHANNEL_TOLERANCE = 24
MAX_DIFF_FRACTION = 0.005


def diff_image(a: bytes, b: bytes) -> bytes:
    out = bytearray(len(a))
    for i in range(0, len(a), 3):
        if any(abs(a[i + k] - b[i + k]) > CHANNEL_TOLERANCE for k in range(3)):
            out[i] = 255
        else:
            g = (a[i] + a[i + 1] + a[i + 2]) // 12
            out[i:i + 3] = bytes((g, g, g))
    return bytes(out)


@pytest.mark.parametrize("name", CHECKPOINTS)
def test_screenshot(boot, name, pytestconfig, output_dir):
    assert name in boot.screenshots, f"checkpoint {name} not reached"
    w, h, rgb = boot.screenshots[name]
    ref = REFERENCE_DIR / f"{name}.png"
    if pytestconfig.getoption("--update-references"):
        REFERENCE_DIR.mkdir(exist_ok=True)
        harness.write_png(ref, w, h, rgb)
        return
    if not ref.exists():
        pytest.fail(f"no reference {ref}; create it with --update-references")
    rw, rh, ref_rgb = harness.read_png(ref)
    assert (rw, rh) == (w, h), f"size {w}x{h} != reference {rw}x{rh}"
    frac = harness.image_diff(rgb, ref_rgb, CHANNEL_TOLERANCE)
    if frac > MAX_DIFF_FRACTION:
        output_dir.mkdir(parents=True, exist_ok=True)
        harness.write_png(output_dir / f"{name}.actual.png", w, h, rgb)
        harness.write_png(output_dir / f"{name}.diff.png", w, h, diff_image(rgb, ref_rgb))
        pytest.fail(f"{name}: {frac:.2%} of pixels differ from {ref.name} (allowed "
                    f"{MAX_DIFF_FRACTION:.2%}); see {output_dir}")


def test_screens_are_not_blank(boot):
    """Guard against references that are just a black screen."""
    for name in ("title_intro", "title_screen", "in_game"):
        _, _, rgb = boot.screenshots[name]
        assert len(set(rgb[i:i + 3] for i in range(0, len(rgb), 3))) > 1, f"{name} is blank"
