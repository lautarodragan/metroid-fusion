"""Power-on to in-game: the game reaches each mode in order and stays sane."""

from scenario import (FILE_SELECT_SUB_FILE_SELECT, FILE_SELECT_SUB_NEW_FILE_INTRO, GAME_MODE_FILE_SELECT_OR_INTRO,
                      GAME_MODE_IN_GAME, GAME_MODE_MAP_SCREEN, GAME_MODE_TITLE, TITLE_SUB_INTRO,
                      TITLE_SUB_TITLE_SCREEN)


def first_index(modes, pred, start=0):
    for i in range(start, len(modes)):
        if pred(modes[i]):
            return i
    return None


def test_first_600_frames_run(emu):
    """The first 600 frames: the main loop runs and the CPU stays in code."""
    emu.load_state(emu.power_on_state)
    bad = []
    counters = []
    for f in range(1, 601):
        emu.run(1)
        if f % 5 == 0:
            if not emu.pc_is_sane():
                bad.append((f, emu.symbolize(emu.cpu_registers()["pc"])))
            counters.append(emu.u16("gFrameCounter16Bit"))
    assert not bad, f"PC outside code: {bad[:5]}"
    # The game loop increments the counter once per frame; a reset would
    # bring it back to zero.
    assert counters == sorted(counters), "frame counter went backwards (console reset?)"
    assert counters[-1] >= 500, f"main loop too slow or stuck: counter {counters[-1]} after 600 frames"


def test_reaches_game_modes_in_order(boot):
    modes = boot.modes()
    steps = [
        ("title intro", lambda m: m[0] == GAME_MODE_TITLE and m[2] == TITLE_SUB_INTRO),
        ("title screen", lambda m: m[0] == GAME_MODE_TITLE and m[2] == TITLE_SUB_TITLE_SCREEN),
        ("file select", lambda m: m[0] == GAME_MODE_FILE_SELECT_OR_INTRO and m[2] == FILE_SELECT_SUB_FILE_SELECT),
        ("new file intro", lambda m: m[0] == GAME_MODE_FILE_SELECT_OR_INTRO
            and m[2] == FILE_SELECT_SUB_NEW_FILE_INTRO),
        ("map screen", lambda m: m[0] == GAME_MODE_MAP_SCREEN),
        ("in game", lambda m: m[0] == GAME_MODE_IN_GAME),
    ]
    i = 0
    for name, pred in steps:
        j = first_index(modes, pred, i)
        assert j is not None, f"never reached {name}; transitions: {boot.transitions}"
        i = j
    assert boot.in_game_frame is not None


def test_no_invalid_cpu_state_during_boot(boot):
    assert not boot.bad_pc, f"PC outside code at (frame, pc): {boot.bad_pc[:5]}"


def test_no_reset_during_boot(boot):
    # InitializeGame sets gMainGameMode to TITLE with gSubGameMode2 = 0; that
    # must only happen right after power-on.
    resets = [f for f, m in boot.transitions if m == (GAME_MODE_TITLE, 0, 0)]
    assert resets == resets[:1] and (not resets or resets[0] <= 2), f"game restarted at frames {resets}"
