#!/bin/bash
# Build and install agbcc (https://github.com/pret/agbcc) so that `agbcc` is on PATH.
#
# Idempotent: re-running with an up-to-date install does nothing.
# Requires: git, make, a host C compiler and binutils-arm-none-eabi.
#
# Environment variables (all optional):
#   AGBCC_REPO    git URL to clone            (default: https://github.com/pret/agbcc)
#   AGBCC_COMMIT  commit to build             (default: pinned below)
#   AGBCC_SRC     where the source lives      (default: $XDG_CACHE_HOME/agbcc-src or ~/.cache/agbcc-src)
#   AGBCC_PREFIX  install prefix              (default: /opt/agbcc)
#   AGBCC_LINK_DIR directory on PATH to symlink into (default: /usr/local/bin; empty to skip)
#   FORCE=1       rebuild and reinstall even if already installed
#
# Install layout:
#   $AGBCC_PREFIX/bin/{agbcc,old_agbcc,agbcc_arm}
#   $AGBCC_PREFIX/lib/{libgcc.a,libc.a}
#   $AGBCC_PREFIX/include/...            (agbcc's libc + ginclude headers)
#   $AGBCC_PREFIX/bin/{libgcc.a,libc.a}  -> ../lib/*   (the Makefile looks for the libs
#                                                     next to `which agbcc`)
#   $AGBCC_LINK_DIR/{agbcc,old_agbcc,agbcc_arm,libgcc.a,libc.a} -> $AGBCC_PREFIX/...
#
# When run under GitHub Actions ($GITHUB_PATH set), $AGBCC_PREFIX/bin is also
# appended to $GITHUB_PATH for subsequent steps.
set -euo pipefail

AGBCC_REPO=${AGBCC_REPO:-https://github.com/pret/agbcc}
AGBCC_COMMIT=${AGBCC_COMMIT:-da598c1d918402c42c0c0d7128ba14567f3175e9}
AGBCC_SRC=${AGBCC_SRC:-${XDG_CACHE_HOME:-$HOME/.cache}/agbcc-src}
AGBCC_PREFIX=${AGBCC_PREFIX:-/opt/agbcc}
AGBCC_LINK_DIR=${AGBCC_LINK_DIR-/usr/local/bin}
FORCE=${FORCE:-0}

STAMP="$AGBCC_PREFIX/.agbcc-commit"
BINS=(agbcc old_agbcc agbcc_arm)
LIBS=(libgcc.a libc.a)

for tool in arm-none-eabi-as arm-none-eabi-ar make git; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "error: '$tool' not found (install binutils-arm-none-eabi, make, git)" >&2
        exit 1
    fi
done

installed_ok() {
    [ -f "$STAMP" ] && [ "$(cat "$STAMP")" = "$AGBCC_COMMIT" ] || return 1
    local f
    for f in "${BINS[@]}"; do [ -x "$AGBCC_PREFIX/bin/$f" ] || return 1; done
    for f in "${LIBS[@]}"; do [ -f "$AGBCC_PREFIX/lib/$f" ] || return 1; done
    return 0
}

if [ "$FORCE" != "1" ] && installed_ok; then
    echo "agbcc $AGBCC_COMMIT already installed in $AGBCC_PREFIX"
else
    # Fetch source
    if [ ! -d "$AGBCC_SRC/.git" ]; then
        echo "Cloning $AGBCC_REPO into $AGBCC_SRC"
        mkdir -p "$(dirname "$AGBCC_SRC")"
        git clone "$AGBCC_REPO" "$AGBCC_SRC"
    fi
    if ! git -C "$AGBCC_SRC" cat-file -e "$AGBCC_COMMIT^{commit}" 2>/dev/null; then
        git -C "$AGBCC_SRC" fetch origin
    fi
    git -C "$AGBCC_SRC" -c advice.detachedHead=false checkout --force "$AGBCC_COMMIT"

    # Build (agbcc's build.sh cleans first, so it is safe to re-run)
    echo "Building agbcc in $AGBCC_SRC"
    (cd "$AGBCC_SRC" && ./build.sh)

    # Install
    echo "Installing agbcc into $AGBCC_PREFIX"
    mkdir -p "$AGBCC_PREFIX/bin" "$AGBCC_PREFIX/lib" "$AGBCC_PREFIX/include"
    for f in "${BINS[@]}"; do install -m 755 "$AGBCC_SRC/$f" "$AGBCC_PREFIX/bin/$f"; done
    for f in "${LIBS[@]}"; do install -m 644 "$AGBCC_SRC/$f" "$AGBCC_PREFIX/lib/$f"; done
    cp -R "$AGBCC_SRC/libc/include/." "$AGBCC_PREFIX/include/"
    cp -R "$AGBCC_SRC/ginclude/." "$AGBCC_PREFIX/include/"
    echo "$AGBCC_COMMIT" > "$STAMP"
fi

# The Makefile derives the lib directory from `dirname $(which agbcc)` without
# resolving symlinks, so the libs must be reachable next to every agbcc on PATH.
for f in "${LIBS[@]}"; do ln -sfn "../lib/$f" "$AGBCC_PREFIX/bin/$f"; done

if [ -n "$AGBCC_LINK_DIR" ]; then
    if mkdir -p "$AGBCC_LINK_DIR" 2>/dev/null && [ -w "$AGBCC_LINK_DIR" ]; then
        for f in "${BINS[@]}"; do ln -sfn "$AGBCC_PREFIX/bin/$f" "$AGBCC_LINK_DIR/$f"; done
        for f in "${LIBS[@]}"; do ln -sfn "$AGBCC_PREFIX/lib/$f" "$AGBCC_LINK_DIR/$f"; done
        echo "Linked agbcc into $AGBCC_LINK_DIR"
    else
        echo "warning: cannot write to $AGBCC_LINK_DIR; add $AGBCC_PREFIX/bin to PATH yourself" >&2
    fi
fi

if [ -n "${GITHUB_PATH:-}" ]; then
    echo "$AGBCC_PREFIX/bin" >> "$GITHUB_PATH"
fi

echo "agbcc ready: $AGBCC_PREFIX/bin/agbcc"
