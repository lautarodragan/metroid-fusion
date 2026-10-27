"""Round-trip tests for tools/open_assets/formats.py (no ROM needed).

Run with: python3 -m pytest tools/open_assets  (or python3 tools/open_assets/test_formats.py)
"""

import os
import random
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import formats  # noqa: E402


def test_lz77_roundtrip_random_and_patterns():
    rng = random.Random(1)
    cases = [b"", b"\x00", bytes(0x800), bytes(range(256)) * 9,
             bytes(rng.randrange(4) for _ in range(5000)),
             formats.placeholder_gfx_4bpp(4096, 7)]
    for data in cases:
        stream = formats.lz77_compress(data)
        assert len(stream) % 4 == 0
        assert formats.lz77_decompress(stream, vram=True) == data


def test_lz77_empty_bg_fits_like_original():
    # A 256x256 BG of tile 0 must fit in 252 bytes (size of rooms/bg0_empty.tm.lz)
    assert len(formats.lz77_compress(bytes(0x800))) <= 252


def test_room_rle_roundtrip():
    rng = random.Random(2)
    for n in (1, 30 * 20, 34 * 14, 6000):
        blocks = [rng.choice((0, 0, 0, 16, 0x8001, 0x123)) for _ in range(n)]
        assert formats.room_rle_decompress(formats.room_rle_compress(blocks)) == blocks


def test_room_rle_empty_layer_is_tiny():
    # Empty layers in the original data take 12 bytes; so must ours.
    assert len(formats.room_rle_compress([0] * (34 * 14))) <= 12


def test_wave_sizes():
    for size in (16, 17, 965, 4096):
        assert len(formats.silent_wave(size)) == size
        assert len(formats.square_wave(size)) == size


if __name__ == "__main__":
    for name, fn in list(globals().items()):
        if name.startswith("test_"):
            fn()
            print("ok", name)
