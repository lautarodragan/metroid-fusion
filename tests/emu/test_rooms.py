"""The first three rooms of the open ROM are connected and traversable.

The scripted walk (scenario.ROOM_WALK) leaves the starting room through its
left hatch and the next room through its upper left door; the room ids in
RAM must follow the door table (src/data/rooms_data.c, sMainDeckDoors):
room 0 door 1 -> room 3, room 3 door 7 -> room 6.
"""

from __future__ import annotations

import pytest


@pytest.mark.parametrize("checkpoint, room", [("room_0", 0), ("room_3", 3), ("room_6", 6)])
def test_walk_reaches_room(boot, checkpoint, room):
    assert checkpoint in boot.rooms, f"walk did not get to {checkpoint}; rooms seen: {boot.rooms}"
    assert boot.rooms[checkpoint] == (0, room), \
        f"at {checkpoint}: (area, room) = {boot.rooms[checkpoint]}, expected (0, {room})"


def test_room_6_arrival_on_the_floor(boot):
    """After the walk Samus stands on the shaft floor (row 39), in front of door 8."""
    assert boot.rooms.get("room_6") == (0, 6)
    x, y = boot.positions["room_6"]
    assert y == 39 * 64 - 1, f"Samus y={y}, expected standing on row 39"
    assert 12 * 64 <= x <= 15 * 64, f"Samus x={x}, expected near the hatch of door 8"


def test_room_3_arrival_on_lower_floor(boot):
    """Room 3 is entered on the lower floor (row 11) on the right."""
    x, y = boot.positions["room_3"]
    assert y == 11 * 64 - 1 and x > 25 * 64, f"Samus at ({x}, {y}) on arrival in room 3"
