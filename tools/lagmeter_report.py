#!/usr/bin/env python3
"""Turn the save file of a LAGMETER build into a lag report.

    python3 tools/lagmeter_report.py mf_us_lagmeter.sav            # rooms with lag, worst first
    python3 tools/lagmeter_report.py mf_us_lagmeter.sav --all      # every room played
    python3 tools/lagmeter_report.py mf_us_lagmeter.sav --csv out.csv
    python3 tools/lagmeter_report.py mf_us_lagmeter.sav --markdown

The log is written by the LAGMETER build (``make LAGMETER=1``, include/lagmeter.h) into two
areas of the 32 KB SRAM that the game itself never uses, next to the normal save files. A
.sav of any size whose first 32 KB are the SRAM works (some flash carts write 64 or 128 KB).
"""

from __future__ import annotations

import argparse
import csv
import struct
import sys
from pathlib import Path

MAGIC = 0x4D47414C            # "LAGM"
VERSION = 1
HEADER = 0x7180
RECORDS_A = 0x71A0
RECORDS_A_COUNT = 272
RECORDS_B = 0x7C00
RECORD_SIZE = 6
FRAME_UNIT = 16               # logic frames per unit of the record
FRAME_CYCLES = 280896

AREAS = ["Main Deck", "Sector 1 (SRX)", "Sector 2 (TRO)", "Sector 3 (PYR)", "Sector 4 (AQA)",
         "Sector 5 (ARC)", "Sector 6 (NOC)", "Test 1", "Test 2", "Test 3"]
ROOMS_PER_AREA = [87, 54, 61, 39, 48, 52, 41, 4, 4, 4]

HEADER_FORMAT = "<IBBHHBBIIIII"   # struct LagMeterSramHeader


class LogError(ValueError):
    pass


def parse(data: bytes) -> dict:
    if len(data) < 0x8000:
        raise LogError(f"save file too small ({len(data)} bytes, expected at least 32768)")
    (magic, version, areas, records, boots, worst_streak, max_load, play_logic, play_lag,
     other_logic, other_lag, play_lagging) = struct.unpack_from(HEADER_FORMAT, data, HEADER)
    if magic != MAGIC:
        raise LogError("no lag log in this save file (was it made by a LAGMETER build?)")
    if version != VERSION or areas != len(AREAS) or records != sum(ROOMS_PER_AREA):
        raise LogError(f"unknown log format (version {version}, {areas} areas, {records} records)")
    rooms = []
    index = 0
    for area, count in enumerate(ROOMS_PER_AREA):
        for room in range(count):
            if index < RECORDS_A_COUNT:
                off = RECORDS_A + index * RECORD_SIZE
            else:
                off = RECORDS_B + (index - RECORDS_A_COUNT) * RECORD_SIZE
            lag, units, streak, load = struct.unpack_from("<HHBB", data, off)
            if lag or units or streak or load:
                rooms.append({"area": area, "area_name": AREAS[area], "room": room,
                              "logic_frames": units * FRAME_UNIT, "lag_frames": lag,
                              "worst_streak": streak, "max_load": load})
            index += 1
    return {"boots": boots, "worst_streak": worst_streak, "max_load": max_load,
            "play_logic_frames": play_logic, "play_lag_frames": play_lag,
            "play_lagging_frames": play_lagging,
            "other_logic_frames": other_logic, "other_lag_frames": other_lag, "rooms": rooms}


def pct(lag: int, logic: int) -> float:
    return 100.0 * lag / (logic + lag) if logic + lag else 0.0


def fmt_time(frames: int) -> str:
    s = frames / 59.7275
    return f"{int(s // 3600)}:{int(s // 60) % 60:02d}:{int(s) % 60:02d}"


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("sav", type=Path)
    ap.add_argument("--all", action="store_true", help="every room played, not only rooms with lag")
    ap.add_argument("--sort", choices=["lag", "rate", "load", "room"], default="lag")
    ap.add_argument("--top", type=int, default=0, help="only the first N rooms")
    ap.add_argument("--csv", type=Path, help="write every room to a CSV file")
    ap.add_argument("--markdown", action="store_true", help="print the tables in Markdown")
    args = ap.parse_args(argv)

    try:
        log = parse(args.sav.read_bytes())
    except LogError as e:
        print(f"{args.sav}: {e}", file=sys.stderr)
        return 1

    rooms = log["rooms"]
    if args.csv:
        with args.csv.open("w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=list(rooms[0]) if rooms else ["area"])
            w.writeheader()
            w.writerows(rooms)

    md = args.markdown
    def row(cells):
        return ("| " + " | ".join(cells) + " |") if md else "  ".join(cells)

    print(f"Sessions (power-ons): {log['boots']}")
    print(f"Played: {log['play_logic_frames']:,} logic frames ({fmt_time(log['play_logic_frames'])}), "
          f"{log['play_lag_frames']:,} lag frames ({pct(log['play_lag_frames'], log['play_logic_frames']):.3f}%), "
          f"{log['play_lagging_frames']:,} logic frames lagged, worst streak {log['worst_streak']}, "
          f"highest load {log['max_load']}%")
    print(f"Other modes (menus, pause, room loads, cutscenes): {log['other_logic_frames']:,} logic frames, "
          f"{log['other_lag_frames']:,} lag frames")
    print()

    # per area
    print(row(["Area", "Rooms played", "Logic frames", "Lag frames", "Lag %", "Worst streak", "Max load %"]))
    if md:
        print("| --- | ---: | ---: | ---: | ---: | ---: | ---: |")
    for a, name in enumerate(AREAS):
        rs = [r for r in rooms if r["area"] == a]
        if not rs:
            continue
        logic = sum(r["logic_frames"] for r in rs)
        lag = sum(r["lag_frames"] for r in rs)
        print(row([f"{name:16s}", f"{len(rs):4d}", f"{logic:10,d}", f"{lag:7,d}", f"{pct(lag, logic):7.3f}",
                   f"{max(r['worst_streak'] for r in rs):3d}", f"{max(r['max_load'] for r in rs):3d}"]))
    print()

    shown = rooms if args.all else [r for r in rooms if r["lag_frames"]]
    key = {"lag": lambda r: -r["lag_frames"], "rate": lambda r: -pct(r["lag_frames"], r["logic_frames"]),
           "load": lambda r: -r["max_load"], "room": lambda r: (r["area"], r["room"])}[args.sort]
    shown = sorted(shown, key=key)
    if args.top:
        shown = shown[:args.top]
    print(row(["Area", "Room", "Logic frames", "Lag frames", "Lag %", "Worst streak", "Max load %"]))
    if md:
        print("| --- | ---: | ---: | ---: | ---: | ---: | ---: |")
    for r in shown:
        print(row([f"{r['area_name']:16s}", f"{r['room']:3d}", f"{r['logic_frames']:10,d}",
                   f"{r['lag_frames']:7,d}", f"{pct(r['lag_frames'], r['logic_frames']):7.3f}",
                   f"{r['worst_streak']:3d}", f"{r['max_load']:3d}"]))
    if not shown:
        print("(no room with lag)" if not args.all else "(no room played)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
