#!/bin/bash
# Check that the build is shiftable:
#   1. tools/check_hardcoded_pointers.py: no literal ROM address in the sources
#   2. build the ROM normally and with `make SHIFT=1` (padding inserted in the
#      middle of the code and at the start of the data)
#   3. tools/check_shift.py: every pointer the build emits follows what it
#      points to in the shifted build
#
# Usage: tools/check_shift.sh
# Environment: REGION (default us), JOBS (default: nproc), SHIFT_AMOUNT
#
# Needs extracted data (tools/extractor.py), from the real or the synthetic
# baserom; tools/check_synthetic.sh leaves it in place. Pointers inside the
# extracted data are not covered: see tools/find_blob_pointers.py.
set -euo pipefail

cd "$(dirname "$0")/.."

REGION=${REGION:-us}
JOBS=${JOBS:-$(nproc 2>/dev/null || echo 4)}
SHIFT_ARGS=()
if [ -n "${SHIFT_AMOUNT:-}" ]; then
    SHIFT_ARGS=(SHIFT_AMOUNT="$SHIFT_AMOUNT")
fi

echo "* Checking for hardcoded ROM addresses"
python3 tools/check_hardcoded_pointers.py

echo "* Building mf_${REGION}.gba"
make -j"$JOBS" REGION="$REGION" > /dev/null

echo "* Building mf_${REGION}_shifted.gba (SHIFT=1)"
make -j"$JOBS" REGION="$REGION" SHIFT=1 "${SHIFT_ARGS[@]}" > /dev/null

echo "* Comparing pointers"
python3 tools/check_shift.py -r "$REGION"
