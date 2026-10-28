#!/bin/bash
# Build the ROM from the open (placeholder) baserom in a separate directory
# and run the emulator tests against it; then do the same with the shift test
# ROM (`make SHIFT=1`, code and data moved) to check that the game still runs
# when addresses change.
#
# Usage: tests/run_emu_tests.sh [--keep] [--no-shift] [pytest args...]
#   e.g. tests/run_emu_tests.sh --update-references
#
# Environment:
#   EMU_BUILD_DIR  build directory (default: a new temporary directory, deleted
#                  afterwards unless --keep). Reusing one makes rebuilds
#                  incremental.
#   JOBS           parallel make jobs (default: nproc)
#
# The working tree is never touched: tracked and untracked (non-ignored)
# files are copied to the build directory, so an existing mf_us_baserom.gba
# (real, synthetic or open) is left alone.
set -euo pipefail

cd "$(dirname "$0")/.."
ROOT=$PWD
JOBS=${JOBS:-$(nproc 2>/dev/null || echo 4)}

KEEP=0
SHIFT=1
PYTEST_ARGS=()
SHIFT_PYTEST_ARGS=()
for arg in "$@"; do
    case "$arg" in
        --keep) KEEP=1 ;;
        --no-shift) SHIFT=0 ;;
        --update-references) PYTEST_ARGS+=("$arg") ;;  # references come from the normal ROM only
        *) PYTEST_ARGS+=("$arg"); SHIFT_PYTEST_ARGS+=("$arg") ;;
    esac
done

if [ -n "${EMU_BUILD_DIR:-}" ]; then
    BUILD=$EMU_BUILD_DIR
    KEEP=1
    mkdir -p "$BUILD"
else
    BUILD=$(mktemp -d -t mf-emu-XXXXXX)
fi
cleanup() {
    if [ "$KEEP" = "0" ]; then
        rm -rf "$BUILD"
    else
        echo "* build kept in $BUILD"
    fi
}
trap cleanup EXIT

echo "* Copying sources to $BUILD"
# -c: tracked, -o --exclude-standard: untracked but not ignored
git ls-files -z -c -o --exclude-standard | (cd "$ROOT" && tar --null -T - -cf -) | tar -xf - -C "$BUILD"

echo "* Building the open ROM (-j$JOBS)"
python3 tools/open_assets/build_open_rom.py -C "$BUILD" -j "$JOBS"

echo "* Running emulator tests"
python3 -m pytest tests/emu --emu-rom "$BUILD/mf_us.gba" "${PYTEST_ARGS[@]}"

if [ "$SHIFT" = "1" ]; then
    echo "* Building the open shift test ROM (SHIFT=1)"
    python3 tools/open_assets/build_open_rom.py -C "$BUILD" -j "$JOBS" --shift
    echo "* Running emulator tests on the shift test ROM"
    python3 -m pytest tests/emu --emu-rom "$BUILD/mf_us_shifted.gba" "${SHIFT_PYTEST_ARGS[@]}"
fi
