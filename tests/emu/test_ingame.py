"""In-game behaviour checked through RAM (gSamusData etc.)."""

from __future__ import annotations

import pytest

from scenario import GAME_MODE_IN_GAME, game_mode

# struct SamusData (include/structs/samus.h)
SAMUS_POSE = "gSamusData+0x01"
SAMUS_X = "gSamusData+0x16"
SAMUS_Y = "gSamusData+0x18"


@pytest.fixture
def in_game(emu, boot):
    assert "in_game" in boot.states, "in-game state not reached"
    emu.load_state(boot.states["in_game"])
    emu.set_input([])
    return emu


def test_in_game_first_room(in_game):
    assert game_mode(in_game)[0] == GAME_MODE_IN_GAME
    # A new game starts in the first room of the Main Deck
    assert in_game.u8("gCurrentArea") == 0
    assert in_game.u8("gCurrentRoom") == 0


def test_walk_right_moves_samus(in_game):
    e = in_game
    e.run(200)  # let the arrival animation finish
    x0 = e.u16(SAMUS_X)
    e.run(40, "RIGHT")
    x1 = e.u16(SAMUS_X)
    assert x1 > x0 + 32, f"holding RIGHT moved Samus from x={x0} to x={x1}"
    e.run(40, "LEFT")
    assert e.u16(SAMUS_X) < x1, "holding LEFT did not move Samus back"


def test_jump(in_game):
    e = in_game
    e.run(200)
    e.run(20, "RIGHT")
    e.run(60)  # land
    y0 = e.u16(SAMUS_Y)
    lowest = y0
    e.set_input("A")
    for _ in range(20):
        e.run(1)
        lowest = min(lowest, e.u16(SAMUS_Y))
    e.run(90, [])
    assert lowest < y0 - 32, f"jump peak y={lowest}, standing y={y0}"
    assert abs(e.u16(SAMUS_Y) - y0) <= 4, "Samus did not land back on the floor"


def test_determinism(emu, boot):
    """Same state + same input -> identical RAM and frames."""
    results = []
    for _ in range(2):
        emu.load_state(boot.states["in_game"])
        for f in range(120):
            emu.run(1, "RIGHT" if f < 60 else "A")
        results.append((emu.ram_hash(), emu.screenshot()[2]))
    assert results[0][0] == results[1][0]
    assert results[0][1] == results[1][1]


def test_power_on_is_deterministic(emu):
    """Two power-ons give the same RAM after the title intro has started."""
    hashes = []
    for _ in range(2):
        emu.load_state(emu.power_on_state)
        emu.run(400)
        hashes.append(emu.ram_hash())
    assert hashes[0] == hashes[1]
