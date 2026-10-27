#!/bin/bash
# Build the ROM from the synthetic baserom and compare it with the golden sha1.
#
# Usage: tools/check_synthetic.sh [--no-clean] [--update]
#   --no-clean  skip `make tidy DATA=1` (incremental build; faster)
#   --update    write the resulting sha1 to mf_<region>_synthetic.sha1 instead
#               of checking it (only for intentional output changes)
#
# Environment: REGION (default us), JOBS (default: nproc)
#
# NOTE: this regenerates mf_<region>_baserom.gba and re-extracts data/ and
# sound/direct_sound_samples/ in place. It refuses to run if a non-synthetic
# baserom (e.g. a real one) is present.
set -euo pipefail

cd "$(dirname "$0")/.."

REGION=${REGION:-us}
JOBS=${JOBS:-$(nproc 2>/dev/null || echo 4)}
CLEAN=1
UPDATE=0
for arg in "$@"; do
    case "$arg" in
        --no-clean) CLEAN=0 ;;
        --update) UPDATE=1 ;;
        *) echo "unknown argument: $arg" >&2; exit 2 ;;
    esac
done

ROM="mf_${REGION}.gba"
GOLDEN="mf_${REGION}_synthetic.sha1"

echo "* Generating synthetic baserom"
python3 tools/make_synthetic_baserom.py -r "$REGION"

if [ "$CLEAN" = "1" ]; then
    echo "* make tidy DATA=1"
    make tidy DATA=1 REGION="$REGION" > /dev/null
fi

echo "* Extracting data"
python3 tools/extractor.py -q -r "$REGION"

echo "* Building $ROM (-j$JOBS)"
make -j"$JOBS" REGION="$REGION" > /dev/null

echo "* Checking data placement"
python3 tools/check_data_placement.py -r "$REGION"

if [ "$UPDATE" = "1" ]; then
    sha1sum "$ROM" | awk '{ print toupper($1) "  " $2 }' > "$GOLDEN"
    echo "* Updated $GOLDEN: $(cat "$GOLDEN")"
else
    echo "* Checking against $GOLDEN"
    if ! sha1sum -c "$GOLDEN"; then
        echo "Synthetic build does NOT match the golden sha1." >&2
        echo "  expected: $(cut -d' ' -f1 "$GOLDEN")" >&2
        echo "  got:      $(sha1sum "$ROM" | cut -d' ' -f1)" >&2
        exit 1
    fi
fi
