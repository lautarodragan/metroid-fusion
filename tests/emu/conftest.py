"""Fixtures for the emulator tests.

The tests need the mGBA libretro core (Debian/Ubuntu: `apt install
libretro-mgba`) and a ROM built from the open baserom (tests/run_emu_tests.sh
builds one). Without either, every test here is skipped with a message.
"""

from __future__ import annotations

import os
import sys
from pathlib import Path

import pytest

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))

import harness  # noqa: E402
import scenario  # noqa: E402

OPEN_MARKER = b"OPEN-BASEROM"


def _rom_path(config) -> Path:
    p = config.getoption("--emu-rom") or os.environ.get("MF_EMU_ROM") or str(ROOT / "mf_us.gba")
    return Path(p).resolve()


@pytest.fixture(scope="session")
def rom_files(pytestconfig):
    core = harness.find_core()
    if not core:
        pytest.skip("mGBA libretro core not found: install it with `sudo apt install libretro-mgba` "
                    f"or point ${harness.CORE_ENV} at mgba_libretro.so")
    rom = _rom_path(pytestconfig)
    map_file = rom.with_suffix(".map")
    if not rom.is_file() or not map_file.is_file():
        pytest.skip(f"{rom} (and its .map) not found: build the open ROM first, "
                    "e.g. with tests/run_emu_tests.sh")
    baserom = rom.with_name(rom.stem + "_baserom.gba")
    if baserom.is_file():
        with open(baserom, "rb") as f:
            if not f.read(len(OPEN_MARKER)) == OPEN_MARKER:
                pytest.skip(f"{rom} was not built from the open baserom; these tests (and their "
                            "reference screenshots) are only meaningful for the open ROM")
    return core, rom, map_file


@pytest.fixture(scope="session")
def emu(rom_files):
    core, rom, map_file = rom_files
    e = harness.Emulator(rom, map_file, core=core)
    e.power_on_state = e.save_state()
    yield e
    e.close()


@pytest.fixture(scope="session")
def boot(emu):
    """The scripted play-through from power-on to in-game (run once)."""
    emu.load_state(emu.power_on_state)
    return scenario.run_boot(emu)


@pytest.fixture(scope="session")
def output_dir(pytestconfig) -> Path:
    p = pytestconfig.getoption("--emu-output") or os.environ.get("MF_EMU_OUTPUT") or str(HERE / "output")
    return Path(p)
