"""The lag meter (lag.py): logic-frame boundaries and lag frame counting."""

from __future__ import annotations

import pytest

import lag


@pytest.fixture
def in_game(emu, boot):
    assert "in_game" in boot.states, "in-game state not reached"
    emu.load_state(boot.states["in_game"])
    emu.set_input([])
    emu.run(200)  # past the arrival animation
    return emu


def test_logic_steps(in_game):
    """Every step runs exactly one logic frame and ends at a boundary."""
    e = in_game
    stepper = lag.LogicStepper(e)
    stepper.sync()
    assert lag.at_boundary(e)
    for keys in (["RIGHT"] * 30 + [[]] * 30):
        before = lag.frame_counter(e)
        frames_before = e.frame_count
        n = stepper.step(keys)
        assert lag.frame_counter(e) == (before + 1) & 0xFFFF
        assert e.frame_count - frames_before == 1 + n
        assert lag.at_boundary(e)


def test_no_lag_in_the_first_room(in_game):
    """Walking in the first room never takes more than a frame per logic frame."""
    stats = lag.count_lag_frames(in_game, 120, "RIGHT")
    assert stats.lag_frames == 0, stats.summary()
    assert stats.logic_frames >= 118
    stepper = lag.LogicStepper(in_game)
    stepper.sync()
    stats = stepper.run(60, ["LEFT"])
    assert stats.logic_frames == 60 and stats.lag_frames == 0, stats.summary()


def test_profile_regions_parse():
    """The region names come from include/profile.h."""
    regions = lag.profile_regions()
    assert regions[0] == "LOOP"
    assert "SPRITE_UPDATE" in regions and "VBLANK" in regions
