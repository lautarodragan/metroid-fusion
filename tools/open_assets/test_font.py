"""Tests for tools/open_assets/font.py (no ROM needed).

Run with: python3 -m pytest tools/open_assets  (or python3 tools/open_assets/test_font.py)
"""

import hashlib
import os
import random
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import font  # noqa: E402
from inventory import Region  # noqa: E402


def test_char_codes():
    # digits are drawn as 0x50 + n by file_select.c, ':' is 0x5A, space 0x40
    assert font.encode("0:9 ", terminate=False) == [0x50, 0x5A, 0x59, 0x40]
    assert font.char_code(ord("A")) == 0x81 and font.char_code(ord("a")) == 0xC1
    assert font.encode("a\nb{ARROW}") == [0xC1, font.CHAR_NEW_LINE, 0xC2,
                                          font.CHAR_NEXT_PAGE_ARROW, font.CHAR_TERMINATOR]


def test_glyphs_fit_their_advance():
    widths = font.load_widths()
    assert len(widths) == 1184
    sheet = font.build_font(widths)
    assert len(sheet) == font.FONT_SIZE
    for byte in range(0x21, 0x7F):
        code = font.char_code(byte)
        adv = widths[code]
        grid = font.fit_glyph(font.base_font.GLYPHS[byte], adv)
        ink_cols = [x for x in range(16) if any(grid[y][x] in (font.INK, font.SHADOW) for y in range(16))]
        assert ink_cols, chr(byte)
        # one free column of letter spacing, nothing past the advance
        assert max(ink_cols) <= adv - 2, (chr(byte), adv, ink_cols)
        assert all(grid[y][x] == 0 for y in range(16) for x in range(adv, 16))
        # the top/bottom tiles land at code * 32 and code * 32 + 0x400
        assert sheet[code * 32:code * 32 + 32] == font.tile_bytes(grid, 0, 0)
        assert sheet[code * 32 + 0x400:code * 32 + 0x420] == font.tile_bytes(grid, 0, 1)


def test_monologue_fits_smallest_region():
    for i in range(19):
        codes = font.monologue_text(i, 32)          # smallest original region: 32 chars
        assert len(codes) <= 32
        assert codes[-1] == font.CHAR_TERMINATOR
        assert codes.count(font.CHAR_NEXT_PAGE_ARROW) == 3


def test_text_tilemaps_fit():
    import formats
    assert len(formats.lz77_compress(font.monologue_tilemap())) <= 1272
    assert len(formats.lz77_compress(font.subtitle_tilemap())) <= 500


def _fake_rom():
    rng = random.Random(3)
    return bytes(rng.randrange(256) for _ in range(0x10000))


def test_copy_font_regions_copies_only_the_font():
    real = _fake_rom()
    regions = [Region(font.FONT_PATH, "data", 0x2000, 0x1000, "font"),
               Region("other.gfx", "data", 0x4000, 0x100, "gfx_raw")]
    rom = bytearray(len(real))
    copied = font.copy_font_regions(rom, real, regions, hashlib.sha1(real).hexdigest(), len(real))
    assert [r.path for r in copied] == [font.FONT_PATH]
    assert rom[0x2000:0x3000] == real[0x2000:0x3000]
    assert not any(rom[:0x2000]) and not any(rom[0x3000:])


def test_copy_font_regions_checks_the_input():
    real = _fake_rom()
    regions = [Region(font.FONT_PATH, "data", 0x2000, 0x1000, "font")]
    for sha1, size in ((font.REAL_ROM_SHA1, len(real)), (hashlib.sha1(real).hexdigest(), 0x800000)):
        try:
            font.copy_font_regions(bytearray(len(real)), real, regions, sha1, size)
        except SystemExit:
            continue
        raise AssertionError("bad input ROM accepted")


if __name__ == "__main__":
    for name, fn in list(globals().items()):
        if name.startswith("test_"):
            fn()
            print("ok", name)
