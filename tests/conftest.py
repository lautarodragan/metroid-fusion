def pytest_addoption(parser):
    group = parser.getgroup("emu", "emulator tests")
    group.addoption("--update-references", action="store_true",
                    help="rewrite tests/emu/reference/*.png from the current run instead of comparing")
    group.addoption("--emu-rom", default=None,
                    help="ROM to test (default: $MF_EMU_ROM or mf_us.gba in the repository root)")
    group.addoption("--emu-output", default=None,
                    help="directory for actual/diff screenshots of failed comparisons "
                         "(default: $MF_EMU_OUTPUT or tests/emu/output)")
