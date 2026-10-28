"""Convert Spleen BDF files into the small Python glyph tables vendored here.

Only printable ASCII (0x20-0x7E) is kept: it is all the open baserom text
uses. Usage (run once, from anywhere; needs a checkout of
https://github.com/fcambus/spleen):

    python3 convert_bdf.py SPLEEN_DIR/spleen-6x12.bdf SPLEEN_DIR/spleen-8x16.bdf

writes spleen_<w>x<h>.py next to this script.
"""

from __future__ import annotations

import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent


def parse_bdf(text: str):
    props, glyphs = {}, {}
    cur = None
    bitmap = None
    for line in text.splitlines():
        parts = line.split()
        if not parts:
            continue
        key = parts[0]
        if bitmap is not None:
            if key == "ENDCHAR":
                glyphs[cur["enc"]] = cur | {"rows": bitmap}
                bitmap, cur = None, None
            else:
                bitmap.append(int(key, 16))
            continue
        if key in ("FONT_ASCENT", "FONT_DESCENT", "FONT_VERSION"):
            props[key] = " ".join(parts[1:]).strip('"')
        elif key == "FONTBOUNDINGBOX":
            props["bbox"] = tuple(int(v) for v in parts[1:])
        elif key == "STARTCHAR":
            cur = {}
        elif key == "ENCODING":
            cur["enc"] = int(parts[1])
        elif key == "BBX":
            cur["bbx"] = tuple(int(v) for v in parts[1:])
        elif key == "BITMAP":
            bitmap = []
    return props, glyphs


def convert(path: Path) -> Path:
    props, glyphs = parse_bdf(path.read_text())
    w, h, _, _ = props["bbox"]
    out = HERE / f"spleen_{w}x{h}.py"
    lines = [
        f'"""Spleen {w}x{h} {props.get("FONT_VERSION", "")}, printable ASCII only.',
        "",
        "Copyright (c) 2018-2026, Frederic Cambus. BSD 2-Clause license, see the",
        "LICENSE file in this directory. Converted from the upstream BDF with",
        "convert_bdf.py; each glyph is a list of rows, '#' = ink.",
        '"""',
        "",
        f"WIDTH = {w}",
        f"HEIGHT = {h}",
        f"ASCENT = {props['FONT_ASCENT']}",
        f"DESCENT = {props['FONT_DESCENT']}",
        "",
        "GLYPHS = {",
    ]
    for code in range(0x20, 0x7F):
        g = glyphs[code]
        bw, bh, _, _ = g["bbx"]
        assert (bw, bh) == (w, h), (code, g["bbx"])
        nbytes = (w + 7) // 8
        rows = []
        for r in g["rows"]:
            bits = "".join("#" if r & (1 << (8 * nbytes - 1 - x)) else "." for x in range(w))
            rows.append(bits)
        lines.append(f"    {code:#04x}: [  # {chr(code)!r}")
        lines += [f'        "{r}",' for r in rows]
        lines.append("    ],")
    lines.append("}")
    out.write_text("\n".join(lines) + "\n")
    return out


if __name__ == "__main__":
    for arg in sys.argv[1:]:
        print("wrote", convert(Path(arg)))
