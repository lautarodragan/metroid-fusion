"""Placeholder sprite graphics (WIP)."""

from __future__ import annotations

import struct

PSPRITE_GUNSHIP = 0x1A

# spriteset number -> [(sprite id, gfx slot)]
SPRITESETS = {
    8: [(PSPRITE_GUNSHIP, 0)],
}


def apply(rom: bytearray, regions, layout) -> list[str]:
    notes = []
    by_sym = {}
    for r in regions:
        s = layout.symbol_of(r)
        if s:
            by_sym[s] = r
    for n, entries in SPRITESETS.items():
        r = by_sym[f"sSpriteset{n}"]
        data = b"".join(bytes(e) for e in entries) + b"\0\0"
        assert len(data) <= r.size
        rom[r.addr:r.addr + r.size] = data + bytes(r.size - len(data))
    notes.append(f"spritesets: {len(SPRITESETS)}")
    return notes
