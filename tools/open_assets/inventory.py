"""Categorize every region listed in database.json.

Usage:
    python3 tools/open_assets/inventory.py            # markdown summary
    python3 tools/open_assets/inventory.py --json     # machine readable
    python3 tools/open_assets/inventory.py --blobs    # list the Blob_* regions

Does not need (and never opens) a ROM. It only reads database.json and scans
src/ and sound/ for the INCBIN / .incbin directives that consume each region.
"""

from __future__ import annotations

import argparse
import json
import re
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DATABASE = ROOT / "database.json"

# category -> (description, kind) where kind is "asset", "layout" or "logic"
CATEGORIES: dict[str, tuple[str, str]] = {
    "sound_sample": ("DirectSound PCM samples (WaveData header + s8 PCM)", "asset"),
    "gfx_lz": ("LZ77 compressed 4bpp tile graphics", "asset"),
    "gfx_raw": ("Uncompressed 4bpp tile graphics", "asset"),
    "gfx_samus": ("Samus/SA-X per frame tile graphics (counts in C)", "asset"),
    "font": ("Text font glyphs (raw)", "asset"),
    "palette": ("BGR555 palettes", "asset"),
    "tilemap_lz": ("LZ77 compressed BG tilemaps (screens, room BG3/BG0)", "asset"),
    "tilemap_raw": ("Uncompressed tilemaps / tile tables", "asset"),
    "tileset_metatiles": ("Tileset block -> 4 tile entries table (.tm)", "layout"),
    "room_bg_rle": ("Room BG0/1/2 block layouts (room RLE)", "layout"),
    "room_clipdata_rle": ("Room collision/behaviour layer (room RLE)", "logic"),
    "misc": ("Other small binary regions", "logic"),
    "blob": ("Not yet understood regions (Blob_*)", "logic"),
}


@dataclass
class Region:
    path: str
    dir: str
    addr: int
    size: int
    category: str
    consumers: list[str] = field(default_factory=list)


def categorize(path: str) -> str:
    base = path.rsplit("/", 1)[-1]
    if base.startswith("Blob_"):
        return "blob"
    if path.startswith("direct_sound_samples/"):
        return "sound_sample"
    if base == "text_characters.gfx":
        return "font"
    if path.startswith("samus/graphics/") or (path.startswith("sa_x/") and re.fullmatch(r"[0-9a-f]+\.gfx", base)):
        return "gfx_samus"
    if base.endswith("_clipdata.rle"):
        return "room_clipdata_rle"
    if base.endswith(".rle") and not base.endswith(".tm.rle"):
        return "room_bg_rle"
    if base.endswith(".gfx.lz"):
        return "gfx_lz"
    if base.endswith(".gfx"):
        return "gfx_raw"
    if base.endswith(".pal"):
        return "palette"
    if base.endswith((".tm.lz", ".tt.lz")):
        return "tilemap_lz"
    if path.startswith("tilesets/") and base.endswith(".tm"):
        return "tileset_metatiles"
    if base.endswith((".tm", ".tt", ".tm.rle")):
        return "tilemap_raw"
    return "misc"


def load_regions(region: str = "us") -> list[Region]:
    with open(DATABASE) as f:
        db = json.load(f)
    out = []
    for e in db:
        addr = e["addr"].get(region)
        if addr is None:
            continue
        count = e["count"]
        if isinstance(count, dict):
            count = count[region]
        out.append(Region(
            path=e["path"],
            dir=e.get("dir", "data"),
            addr=int(addr, 16),
            size=int(count, 16) * e["size"],
            category=categorize(e["path"]),
        ))
    return out


INCBIN_RE = re.compile(r'(?:INCBIN_\w+|_INCBIN_\w+|\.incbin)\s*\(?\s*"([^"]+)"')


def scan_consumers() -> dict[str, list[str]]:
    """Map 'dir/path' -> list of source files that include it."""
    users: dict[str, list[str]] = defaultdict(list)
    for top in ("src", "sound", "asm"):
        for p in (ROOT / top).rglob("*"):
            if p.suffix not in (".c", ".s", ".h", ".inc") or not p.is_file():
                continue
            text = p.read_text(errors="replace")
            for m in INCBIN_RE.finditer(text):
                users[m.group(1)].append(str(p.relative_to(ROOT)))
    return users


def attach_consumers(regions: list[Region]) -> None:
    users = scan_consumers()
    for r in regions:
        r.consumers = sorted(set(users.get(f"{r.dir}/{r.path}", [])))


def summarize(regions: list[Region]) -> dict[str, dict]:
    summary: dict[str, dict] = {}
    for cat, (desc, kind) in CATEGORIES.items():
        rs = [r for r in regions if r.category == cat]
        summary[cat] = {
            "description": desc,
            "kind": kind,
            "count": len(rs),
            "bytes": sum(r.size for r in rs),
        }
    return summary


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true", help="print JSON instead of markdown")
    ap.add_argument("--blobs", action="store_true", help="list Blob_* regions and their consumers")
    args = ap.parse_args()

    regions = load_regions()
    attach_consumers(regions)
    summary = summarize(regions)
    total = sum(r.size for r in regions)

    if args.json:
        print(json.dumps({"total_bytes": total, "categories": summary,
                          "unreferenced": [r.path for r in regions if not r.consumers]}, indent=2))
        return

    if args.blobs:
        print("| Blob | ROM offset | Bytes | Consumer |")
        print("|---|---|---:|---|")
        for r in sorted((r for r in regions if r.category == "blob"), key=lambda r: r.addr):
            print(f"| `{r.path}` | 0x{r.addr:06X} | {r.size} | {', '.join(r.consumers) or '(none found)'} |")
        return

    print("| Category | Kind | Regions | Bytes | KiB | % of extracted |")
    print("|---|---|---:|---:|---:|---:|")
    for cat, s in sorted(summary.items(), key=lambda kv: -kv[1]["bytes"]):
        print(f"| {cat} ({s['description']}) | {s['kind']} | {s['count']} | {s['bytes']} | "
              f"{s['bytes'] / 1024:.1f} | {100 * s['bytes'] / total:.1f}% |")
    print(f"| **total** | | **{len(regions)}** | **{total}** | **{total / 1024:.1f}** | 100% |")
    by_kind: dict[str, int] = defaultdict(int)
    for s in summary.values():
        by_kind[s["kind"]] += s["bytes"]
    print()
    for kind, b in by_kind.items():
        print(f"- {kind}: {b} bytes ({100 * b / total:.1f}%)")
    unref = [r.path for r in regions if not r.consumers]
    print(f"- regions with no INCBIN consumer found: {len(unref)}" + (f" ({', '.join(unref[:5])})" if unref else ""))


if __name__ == "__main__":
    main()
