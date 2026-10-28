"""Placeholder graphics for projectiles, effects and sprites (enemies, pads...).

Like samus_gfx.py, every picture is drawn on a canvas in object-local
coordinates and cut into tiles through the OAM frames defined in C
(see oam_art.py). What is drawn depends on the name of the frame's
animation (``struct FrameData`` array) and its frame number:

- the common sprites sheet (``sCommonSpritesGfx``, OBJ tiles 64-511):
  particle effects (explosions, smoke, splashes, X absorption...), the
  parts of projectiles that live there (missile exhaust, bombs), the free
  floating X parasites, and the HUD tiles from hud_gfx.py on top;
- the beam blocks (two rows of 20 tiles per beam, loaded at OBJ tile row 4
  when the beam is equipped) and the missile blocks (4x2 tiles at column 28);
- the sprite blocks (``sXxxGfx`` in src/data/sprites/*.c, loaded at OBJ tile
  512 + 64 * slot): pads, gunship and gates get dedicated drawings, any other
  sprite a generic creature (body, eyes, legs or fins) whose shape follows
  its frame's outline and whose colours come from its name;
- spritesets (blobs in src/data/sprite_data.c): spriteset 8 (the first room)
  holds the gunship, which the new game sequence needs before Samus is drawn.

Palettes: the common sheet and the beams use the effects layout in
oam_art.py (FX_*), sprites the creature layout below (CR_*).
"""

from __future__ import annotations

import hashlib
import math
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import hud_gfx  # noqa: E402
import oam_art as A  # noqa: E402
from oam_art import (FX_B1, FX_B2, FX_B3, FX_BLACK, FX_E1, FX_E2, FX_E3, FX_E4, FX_G1, FX_G2, FX_G3,  # noqa: E402
                     FX_K1, FX_K2, FX_K3, FX_WHITE)

PSPRITE_GUNSHIP = 0x1A

# spriteset number -> [(sprite id, gfx slot)]
SPRITESETS = {
    8: [(PSPRITE_GUNSHIP, 0)],
}

COMMON_FIRST_TILE = 64            # sCommonSpritesGfx is copied to OBJ tile 64
COMMON_TILES = 14 * 32
SPRITE_FIRST_TILE = 512           # gfx slot 0
BEAMS = ("Normal", "Charge", "Wide", "Plasma", "Wave", "Ice")
BEAM_ENERGY = {"Normal": "yellow", "Charge": "orange", "Wide": "magenta", "Plasma": "green",
               "Wave": "violet", "Ice": "cyan"}
# OBJ palette rows 2-7 (common.pal)
COMMON_ENERGY = ["yellow", "orange", "cyan", "green", "green", "magenta"]


def seed(name: str) -> int:
    return int.from_bytes(hashlib.sha1(name.encode()).digest()[:4], "little")


def bbox(entries):
    return (min(e.x for e in entries), min(e.y for e in entries),
            max(e.x + e.w for e in entries), max(e.y + e.h for e in entries))


# ---------------------------------------------------------------------------
# Frames by animation
# ---------------------------------------------------------------------------

def frames_by_anim(d, prefix_files=None):
    """[(anim name, frame index, frame count, oam name)], every OAM frame once.

    Frames referenced by a FrameData array get that array's name; others
    keep their own name.
    """
    out = []
    seen = set()
    for anim, frames in d.frames.items():
        for i, (oam, _) in enumerate(frames):
            if oam in d.oam:
                out.append((anim, i, len(frames), oam))
                seen.add(oam)
    for oam in d.oam:
        if oam not in seen:
            m = re.match(r"(.*?)_?Frame(\d+)$", oam)
            out.append((m.group(1) if m else oam, int(m.group(2)) if m else 0, 1, oam))
    return out


DIRS = {"horizontal": (-1.0, 0.0), "diagonal": (-0.7071, -0.7071), "vertical": (0.0, -1.0)}


def direction(name: str, B):
    n = name.lower()
    for k, v in DIRS.items():
        if k in n:
            return v
    w, h = B[2] - B[0], B[3] - B[1]
    return (0.0, -1.0) if h > w else (-1.0, 0.0)


# ---------------------------------------------------------------------------
# Effects
# ---------------------------------------------------------------------------

def draw_beam(cv, name, i, n, B):
    dx, dy = direction(name, B)
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    w, h = B[2] - B[0], B[3] - B[1]
    ext = abs(dx) * w + abs(dy) * h if abs(dx) < 0.9 and abs(dy) < 0.9 else (w if abs(dx) > 0.5 else h)
    if abs(dx) > 0.1 and abs(dy) > 0.1:
        ext = min(w, h) * 1.3
    charged = "Charged" in name
    half = max(2.0, ext / 2 - 2.5)
    r = 3.2 if charged else 2.0
    px, py = -dy, dx
    lanes = [0.0]
    if "Wide" in name or "Double" in name:
        lanes = [-3.5, 3.5] if "Double" in name else [-4.0, 0.0, 4.0]
        r = min(r, 1.8)
    for off in lanes:
        ox, oy = cx + px * off, cy + py * off
        if "Wave" in name:
            for t in range(-int(half), int(half) + 1):
                s = math.sin(t * 0.8 + i * 1.6) * 2.5
                cv.disc(ox + dx * t + px * s, oy + dy * t + py * s, r * 0.8, FX_E2)
            cv.disc(ox + dx * half, oy + dy * half, r, FX_E4)
            continue
        if "Ice" in name:
            k = r + 1.5
            pts = [(ox + dx * (half + 1), oy + dy * (half + 1)), (ox + px * k, oy + py * k),
                   (ox - dx * (half + 1), oy - dy * (half + 1)), (ox - px * k, oy - py * k)]
            cv.poly(pts, FX_E2)
            cv.capsule(ox - dx * half * 0.5, oy - dy * half * 0.5, ox + dx * half * 0.6, oy + dy * half * 0.6, 1.0, FX_E4)
            continue
        cv.capsule(ox - dx * half, oy - dy * half, ox + dx * half, oy + dy * half, r * 0.6, FX_E1, r)
        cv.capsule(ox - dx * half * 0.6, oy - dy * half * 0.6, ox + dx * half, oy + dy * half, r * 0.45, FX_E3, r * 0.75)
        cv.capsule(ox, oy, ox + dx * half * 0.9, oy + dy * half * 0.9, 0.6, FX_E4, r * 0.45)
    cv.outline(FX_BLACK)


def draw_missile(cv, name, i, n, entries, B, sheet_only=None):
    dx, dy = direction(name, B)
    if "Tumbling" in name:
        a = math.radians(45 * i)
        dx, dy = math.cos(a), math.sin(a)
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    w, h = B[2] - B[0], B[3] - B[1]
    L = (w if abs(dx) > 0.9 else h if abs(dy) > 0.9 else min(w, h) * 1.2) / 2 - 1.5
    px, py = -dy, dx
    body = FX_B2 if "Ice" in name else FX_G2 if "Diffusion" in name else FX_K3
    tail_x, tail_y = cx - dx * L, cy - dy * L
    # exhaust flame behind
    cv.capsule(tail_x - dx * 2, tail_y - dy * 2, tail_x + dx * 2, tail_y + dy * 2, 1.0 + (i % 2), FX_E3, 2.2)
    cv.capsule(cx - dx * (L - 3), cy - dy * (L - 3), cx + dx * (L - 2.5), cy + dy * (L - 2.5), 2.4, body)
    cv.disc(cx + dx * (L - 2.5), cy + dy * (L - 2.5), 2.2, FX_E2 if "Ice" not in name else FX_B3)
    for s in (-1, 1):  # fins
        cv.capsule(cx - dx * (L - 4), cy - dy * (L - 4), cx - dx * (L - 2) + px * 3.5 * s,
                   cy - dy * (L - 2) + py * 3.5 * s, 0.8, FX_K2)
    cv.outline(FX_BLACK)


def draw_bomb(cv, name, i, n, B):
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    r = max(2.5, min(B[2] - B[0], B[3] - B[1]) / 2 - 1.5)
    big = "Power" in name
    cv.disc(cx, cy, r, FX_K1 if not big else FX_E1, shade=(FX_K2, FX_BLACK) if not big else None)
    cv.disc(cx, cy, r * 0.45, FX_E4 if i % 2 == 0 else FX_E2)
    cv.outline(FX_BLACK)


def draw_burst(cv, name, i, n, B, palette=(FX_E1, FX_E2, FX_E3, FX_E4)):
    """Explosion: spiky ring growing with the frame number."""
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    R = min(B[2] - B[0], B[3] - B[1]) / 2 - 1
    p = (i + 1) / max(1, n)
    r = max(2.0, R * (0.45 + 0.55 * p))
    rot = seed(name) % 360
    spikes = []
    for k in range(10):
        a = math.radians(rot + k * 36)
        rr = r if k % 2 == 0 else r * 0.6
        spikes.append((cx + math.cos(a) * rr, cy + math.sin(a) * rr))
    cv.poly(spikes, palette[1] if p < 0.75 else palette[0])
    cv.disc(cx, cy, r * 0.55 * (1.2 - p), palette[2])
    if p < 0.6:
        cv.disc(cx, cy, r * 0.3, palette[3])
    if p > 0.7:  # dissolving: punch holes
        for k in range(6):
            a = math.radians(rot + 30 + k * 60)
            cv.disc(cx + math.cos(a) * r * 0.5, cy + math.sin(a) * r * 0.5, r * 0.22 * p, 0)


def draw_puffs(cv, name, i, n, B, cols=(FX_K1, FX_K2, FX_K3)):
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    R = min(B[2] - B[0], B[3] - B[1]) / 2 - 1
    p = (i + 1) / max(1, n)
    s = seed(name)
    for k in range(4):
        a = math.radians((s + k * 97) % 360)
        d = R * 0.45 * p
        rr = max(1.5, R * (0.55 - 0.25 * p))
        cv.disc(cx + math.cos(a) * d, cy + math.sin(a) * d, rr, cols[1], shade=(cols[2], cols[0]))


def draw_drops(cv, name, i, n, B):
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    R = min(B[2] - B[0], B[3] - B[1]) / 2 - 1
    if "Bubble" in name:
        for k in range(3):
            cv.disc(cx + (k - 1) * R * 0.5, cy - k * R * 0.4, max(1.2, R * 0.35), FX_B3)
            cv.disc(cx + (k - 1) * R * 0.5, cy - k * R * 0.4, max(0.5, R * 0.35 - 1), 0)
        return
    p = (i + 1) / max(1, n)
    for k in range(5):
        a = math.radians(200 + k * 35)
        d = R * (0.3 + 0.6 * p)
        cv.disc(cx + math.cos(a) * d, cy + math.sin(a) * d + R * 0.3, max(1.0, R * 0.25), FX_B2, shade=(FX_B3, FX_B1))
    cv.outline(FX_BLACK)


def draw_x(cv, name, i, n, B, cols=None):
    """Floating X parasite: a membrane with a bright nucleus."""
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    R = max(2.0, min(B[2] - B[0], B[3] - B[1]) / 2 - 1)
    cols = cols or (FX_E1, FX_E2, FX_E3, FX_E4)
    wob = math.sin(i * 1.7) * 0.8
    pts = []
    for k in range(12):
        a = math.radians(k * 30)
        rr = R * (0.85 + 0.15 * math.sin(3 * a + i)) + (wob if k % 2 else -wob)
        pts.append((cx + math.cos(a) * rr, cy + math.sin(a) * rr))
    cv.poly(pts, cols[1])
    cv.disc(cx - R * 0.15, cy - R * 0.15, R * 0.5, cols[2])
    cv.disc(cx - R * 0.25, cy - R * 0.25, max(1.0, R * 0.22), cols[3])
    cv.outline(FX_BLACK)


def draw_sparkle(cv, name, i, n, B):
    cx, cy = (B[0] + B[2]) / 2, (B[1] + B[3]) / 2
    R = max(1.5, min(B[2] - B[0], B[3] - B[1]) / 2 - 1)
    p = (i + 1) / max(1, n)
    r = R * (1.1 - 0.5 * p)
    cv.capsule(cx - r, cy, cx + r, cy, 0.7, FX_E3)
    cv.capsule(cx, cy - r, cx, cy + r, 0.7, FX_E3)
    cv.capsule(cx - r * 0.5, cy - r * 0.5, cx + r * 0.5, cy + r * 0.5, 0.5, FX_E2)
    cv.capsule(cx - r * 0.5, cy + r * 0.5, cx + r * 0.5, cy - r * 0.5, 0.5, FX_E2)
    cv.disc(cx, cy, max(1.0, r * 0.3), FX_E4)


def draw_effect(cv, name, i, n, entries):
    B = bbox(entries)
    low = name.lower()
    if "trail" in low:
        if "missile" in low:
            draw_puffs(cv, name, i, n, B, cols=(FX_E1, FX_E2, FX_E3))
        else:
            draw_sparkle(cv, name, i, n, B)
    elif "beam" in low and "fire" not in low:
        draw_beam(cv, name, i, n, B)
    elif "missile" in low and "explosion" not in low:
        draw_missile(cv, name, i, n, entries, B)
    elif "bomb" in low and "explosion" not in low:
        draw_bomb(cv, name, i, n, B)
    elif "xparasite" in low.replace("_", "") or "absorb" in low or "xtrail" in low.replace("_", "") \
            or re.search(r"(^|[a-z])X(Oam|_)", name):
        cols = (FX_G1, FX_G2, FX_G3, FX_WHITE) if "Health" in name or "Green" in name else \
            (FX_B1, FX_B2, FX_B3, FX_WHITE) if "Missile" in name or "Ice" in name or "Blue" in name else None
        draw_x(cv, name, i, n, B, cols)
    elif "ice" in low and ("explosion" in low or "cloud" in low):
        draw_burst(cv, name, i, n, B, palette=(FX_B1, FX_B2, FX_B3, FX_WHITE))
    elif any(k in low for k in ("explosion", "killed", "hit", "fire")):
        draw_burst(cv, name, i, n, B)
    elif any(k in low for k in ("smoke", "dust", "cloud", "debris")):
        draw_puffs(cv, name, i, n, B)
    elif any(k in low for k in ("water", "splash", "drop", "bubble", "environmental")):
        draw_drops(cv, name, i, n, B)
    else:
        draw_sparkle(cv, name, i, n, B)


# ---------------------------------------------------------------------------
# Sprites
# ---------------------------------------------------------------------------

# creature palette layout
CR_OUT = 1
CR_B1, CR_B2, CR_B3 = 2, 3, 4          # body
CR_S1, CR_S2, CR_S3 = 5, 6, 7          # secondary (belly, legs, shell)
CR_EYE, CR_PUPIL = 8, 9
CR_G1, CR_G2, CR_G3 = 10, 11, 12       # glow (pads, cores, lights)
CR_K1, CR_K2, CR_K3 = 13, 14, 15       # metal grey


def hsv(h, s, v):
    h = (h % 360) / 60
    c = v * s
    x = c * (1 - abs(h % 2 - 1))
    r, g, b = [(c, x, 0), (x, c, 0), (0, c, x), (0, x, c), (x, 0, c), (c, 0, x)][int(h) % 6]
    m = v - c
    return tuple(int((q + m) * 255) for q in (r, g, b))


GLOW = {"save": 120, "recharge": 200, "navigation": 45, "data": 280, "security": 0,
        "elevator": 180, "operations": 30, "gunship": 190}


def creature_palette(name: str, row: int = 0):
    h = seed(name) % 360
    glow_h = next((v for k, v in GLOW.items() if k in name), (h + 180) % 360)
    if "x_parasite" in name or name.endswith("_x") or "core_x" in name:
        h, glow_h = 55, 30
    body = [hsv(h, 0.65, v) for v in (0.35, 0.65, 0.95)]
    sec = [hsv(h + 40, 0.45, v) for v in (0.3, 0.55, 0.85)]
    glow = [hsv(glow_h, 0.8, v) for v in (0.5, 0.85, 1.0)]
    grey = [(64, 68, 84), (128, 132, 150), (200, 204, 220)]
    pal = [(0, 0, 0), (12, 10, 20), *body, *sec, (250, 250, 240), (20, 10, 10), *glow, *grey]
    if row:
        pal = [pal[0], pal[1]] + [A.mix(c, (255, 255, 255), 0.15 * row) for c in pal[2:]]
    return pal


def draw_pad(cv, name, i, n, B):
    """Machinery on the floor: a base with a glowing plate."""
    x0, y0, x1, y1 = B
    cx = (x0 + x1) / 2
    w = x1 - x0
    base_top = max(y0, y1 - 8)
    cv.poly([(x0 + 1, y1 - 1), (x1 - 1, y1 - 1), (x1 - 4, base_top), (x0 + 4, base_top)], CR_K2)
    cv.rect(x0 + 4, base_top, x1 - 5, base_top + 1, CR_K3)
    glow = CR_G3 if i % 2 == 0 else CR_G2
    cv.rect(cx - w / 4, base_top - 1, cx + w / 4, base_top, glow)
    if y1 - y0 > 16:  # a console/arch above the plate
        cv.rect(x0 + 2, y0 + 1, x0 + 5, base_top - 1, CR_K1)
        cv.rect(x1 - 6, y0 + 1, x1 - 3, base_top - 1, CR_K1)
        cv.rect(x0 + 2, y0 + 1, x1 - 3, y0 + 3, CR_K2)
        for k in range(int(y0) + 6, int(base_top) - 2, 5):
            cv.rect(x0 + 3, k, x0 + 4, k + 1, glow)
            cv.rect(x1 - 5, k, x1 - 4, k + 1, glow)
    cv.outline(CR_OUT)


def draw_gunship(cv, name, i, n, B):
    x0, y0, x1, y1 = B
    cx, cy = (x0 + x1) / 2, (y0 + y1) / 2
    w, h = x1 - x0, y1 - y0
    if w < 24 or h < 12:  # small parts (beam, lights)
        cv.ellipse(cx, cy, w / 2 - 1, h / 2 - 1, CR_G2)
        cv.ellipse(cx, cy, max(1, w / 4), max(1, h / 4), CR_G3)
        return
    cv.ellipse(cx, cy + h * 0.1, w * 0.48, h * 0.3, CR_K2)              # hull
    cv.ellipse(cx, cy + h * 0.2, w * 0.4, h * 0.12, CR_K1)
    cv.ellipse(cx, cy - h * 0.12, w * 0.18, h * 0.2, CR_G2)             # canopy
    cv.ellipse(cx - w * 0.05, cy - h * 0.18, w * 0.07, h * 0.08, CR_G3)
    for s in (-1, 1):                                                   # wings / engines
        cv.poly([(cx + s * w * 0.2, cy), (cx + s * w * 0.49, cy + h * 0.25),
                 (cx + s * w * 0.45, cy + h * 0.4), (cx + s * w * 0.15, cy + h * 0.25)], CR_B2)
        cv.disc(cx + s * w * 0.38, cy + h * 0.33, min(w, h) * 0.07, CR_G3)
    cv.outline(CR_OUT)


def draw_gate(cv, name, i, n, B):
    x0, y0, x1, y1 = B
    cv.rect(x0 + 1, y0, x1 - 2, y1 - 1, CR_K2)
    cv.rect(x0 + 2, y0, x0 + 2, y1 - 1, CR_K3)
    for k in range(int(y0) + 3, int(y1) - 2, 6):
        cv.rect(x0 + 2, k, x1 - 3, k + 1, CR_G2 if i % 2 == 0 else CR_G3)
    cv.outline(CR_OUT)


def draw_creature(cv, name, i, n, entries):
    """Generic monster fitted to the frame outline, facing left."""
    B = bbox(entries)
    x0, y0, x1, y1 = B
    w, h = x1 - x0, y1 - y0
    cx, cy = (x0 + x1) / 2, (y0 + y1) / 2
    s = seed(name.split("Oam")[0])
    if w <= 8 and h <= 8:          # small projectiles / particles
        cv.disc(cx, cy, 2.6, CR_G2)
        cv.disc(cx - 0.5, cy - 0.5, 1.2, CR_G3)
        cv.outline(CR_OUT)
        return
    phase = i % 2
    flying = "fly" in name.lower() or "swim" in name.lower() or s % 4 == 0
    rx, ry = w / 2 - 1.5, h / 2 - 1.5
    if not flying and h >= 12:
        # body above legs
        leg_h = min(6.0, h * 0.28)
        ry = (h - leg_h) / 2 - 1
        bcy = y0 + 1 + ry
        nlegs = 2 if w < 24 else 3
        for k in range(nlegs):
            lx = x0 + 3 + (w - 6) * (k + 0.5) / nlegs
            sw = (2 if (k + phase) % 2 else -2)
            cv.capsule(lx, bcy + ry * 0.5, lx + sw, y1 - 1.5, 1.6, CR_S1)
            cv.ellipse(lx + sw - 1, y1 - 1.5, 2.2, 1.2, CR_S2)
    else:
        bcy = cy + (0.8 if phase else -0.8)
    cv.ellipse(cx, bcy, rx, ry, CR_B2)
    cv.ellipse(cx + rx * 0.2, bcy + ry * 0.35, rx * 0.6, ry * 0.45, CR_S2)   # belly
    cv.ellipse(cx - rx * 0.1, bcy - ry * 0.45, rx * 0.55, ry * 0.25, CR_B3)  # highlight
    # spikes / crest on top
    nsp = s % 4
    for k in range(nsp):
        sx = cx - rx * 0.4 + k * rx * 0.5
        top = bcy - ry
        cv.poly([(sx - 1.5, top + 1.5), (sx + 1.5, top + 1.5), (sx + 0.5, top - 2.5)], CR_S3)
    # eye on the left (facing direction)
    ex, ey = cx - rx * 0.55, bcy - ry * 0.2
    er = max(1.5, min(rx, ry) * 0.3)
    cv.disc(ex, ey, er, CR_EYE)
    cv.disc(ex - er * 0.35, ey, max(0.8, er * 0.5), CR_PUPIL)
    if flying and w > 14:  # fins / wings
        cv.poly([(cx + rx * 0.3, bcy - ry * 0.2), (x1 - 1, bcy - ry - (2 if phase else 0)),
                 (x1 - 2, bcy + ry * 0.2)], CR_S1)
    cv.outline(CR_OUT)


def draw_segments(cv, name, i, n, entries):
    """Creature made of one rounded plate per OAM piece.

    Sprite frames reuse the same tiles in different arrangements (a head
    piece moves, a leg piece is flipped...), so each piece is drawn as a
    self-contained plate: whatever the arrangement, the result is a cluster
    of plates, never a picture cut in the wrong place. The front-most top
    piece (sprites face left) gets an eye, the lowest pieces the secondary
    colour (legs, shell, base).
    """
    B = bbox(entries)
    x0, y0, x1, y1 = B
    s = seed(name.split("Oam")[0])
    head = min(entries, key=lambda e: (e.x + (e.y - y0) * 0.6, e.y))
    for e in sorted(entries, key=lambda e: -(e.w * e.h)):
        cx, cy = e.x + e.w / 2, e.y + e.h / 2
        low = e.y + e.h >= y1 - 1 and e.y > y0 + 4 and e.h <= 16
        body = (CR_S1, CR_S2, CR_S3) if low else (CR_B1, CR_B2, CR_B3)
        rx, ry = e.w / 2 - 0.8, e.h / 2 - 0.8
        cv.ellipse(cx, cy, rx + 0.6, ry + 0.6, CR_OUT)
        cv.ellipse(cx, cy, rx, ry, body[1])
        cv.ellipse(cx - rx * 0.25, cy - ry * 0.35, rx * 0.5, ry * 0.35, body[2])
        cv.ellipse(cx + rx * 0.2, cy + ry * 0.5, rx * 0.6, ry * 0.25, body[0])
        if s % 3 == 0 and e.w >= 16 and not low:  # stripes
            for k in range(int(e.x) + 4, int(e.x + e.w) - 3, 5):
                cv.line(k, cy - ry * 0.6, k, cy + ry * 0.6, body[0])
        if e is head:
            er = max(1.3, min(rx, ry) * 0.38)
            ex, ey = cx - rx * 0.45, cy - ry * 0.15
            cv.disc(ex, ey, er + 0.6, CR_OUT)
            cv.disc(ex, ey, er, CR_EYE)
            cv.disc(ex - er * 0.35, ey, max(0.7, er * 0.5), CR_PUPIL)


def draw_sprite_frame(cv, file_stem, anim, i, n, entries):
    stem = file_stem
    if "pad" in stem or "stabilizer" in stem or "elevator" in stem:
        draw_pad(cv, anim, i, n, bbox(entries))
    elif "gunship" in stem:
        draw_gunship(cv, anim, i, n, bbox(entries))
    elif stem in ("gate", "missile_hatch", "pillar", "shake_trigger") or "hatch" in stem:
        draw_gate(cv, anim, i, n, bbox(entries))
    elif "x_parasite" in stem or stem.endswith("core_x") or stem.endswith("_x"):
        draw_x(cv, anim, i, n, bbox(entries), cols=(CR_B1, CR_B2, CR_G2, CR_G3))
    else:
        draw_segments(cv, anim, i, n, entries)


# ---------------------------------------------------------------------------
# Painting sheets
# ---------------------------------------------------------------------------

def paint(sheet, frames, oam, draw, lo, hi, owner_of=lambda a: a, canvas=128):
    """Cut every frame (anim, i, n, oam name) whose tiles fall in [lo, hi)
    into ``sheet``; tiles already painted are kept (first frame wins)."""
    for anim, i, n, name in frames:
        entries = [e for e in oam[name] if any(lo <= t < hi for _, _, t in e.tiles())]
        if not entries:
            continue
        free = [t for e in entries for _, _, t in e.tiles() if lo <= t < hi and sheet.owner[t] is None]
        if not free:
            continue
        cv = A.Canvas(canvas)
        draw(cv, anim, i, n, entries)
        sheet.cut(cv, entries, owner=owner_of(anim), tile_filter=lambda t: lo <= t < hi)


def effects_data():
    return A.parse_c(A.c_files("src/data/particle_data.c", "src/data/projectile_data.c"))


def common_sheet(fx=None, sprites=None) -> A.TileSheet:
    fx = fx or effects_data()
    sheet = A.TileSheet(1024)
    for t, px in hud_gfx.hud_sheet_tiles().items():
        sheet.tiles[t] = bytearray(px)
        sheet.owner[t] = "hud"
    lo, hi = COMMON_FIRST_TILE, COMMON_FIRST_TILE + COMMON_TILES
    frames = frames_by_anim(fx)
    # projectile pieces first (they are always on screen), then particles
    frames.sort(key=lambda f: (0 if "Missile" in f[0] or "Bomb" in f[0] else 1, f[0], f[1]))
    paint(sheet, frames, fx.oam, draw_effect, lo, hi)
    if sprites:
        for stem, d in sprites.items():
            paint(sheet, frames_by_anim(d), d.oam,
                  lambda cv, a, i, n, e, stem=stem: draw_effect(cv, stem + "_" + a, i, n, e), lo, hi)
    return sheet


def beam_blocks(fx) -> dict:
    out = {}
    frames = frames_by_anim(fx)
    for beam in BEAMS:
        sheet = A.TileSheet(1024)
        mine = [f for f in frames if f"{beam}Beam" in f[0] or f"{beam}Beam" in f[3]]
        paint(sheet, mine, fx.oam, draw_effect, 4 * 32, 4 * 32 + 52)
        top = A.tiles_to_bytes(sheet.tiles[4 * 32:4 * 32 + 20])
        bottom = A.tiles_to_bytes(sheet.tiles[5 * 32:5 * 32 + 20])
        key = beam.lower()
        out[f"projectiles/{key}_beam_top.gfx"] = top
        out[f"projectiles/{key}_beam_bottom.gfx"] = bottom
        out[f"projectiles/{key}_beam.pal"] = A.pal_bytes(A.fx_palette(BEAM_ENERGY[beam]))
    missiles = {"normal": "NormalSuperMissile", "super": "NormalSuperMissile", "ice": "IceMissile",
                "diffusion": "DiffusionMissile"}
    for key, prefix in missiles.items():
        sheet = A.TileSheet(1024)
        mine = [f for f in frames if prefix in f[0] or "Tumbling" in f[0]]
        if key == "super":
            mine = [(a.replace("NormalSuper", "Super"), i, n, o) for a, i, n, o in mine]
        lo = 4 * 32 + 28

        def draw(cv, a, i, n, e, key=key):
            draw_missile(cv, a if key != "super" else a + "Super", i, n, e, bbox(e))
        for row in (4, 5):
            paint(sheet, mine, fx.oam, draw, row * 32 + 28, row * 32 + 32)
        out[f"projectiles/{key}_missile_top.gfx"] = A.tiles_to_bytes(sheet.tiles[4 * 32 + 28:4 * 32 + 32])
        out[f"projectiles/{key}_missile_bottom.gfx"] = A.tiles_to_bytes(sheet.tiles[5 * 32 + 28:5 * 32 + 32])
    # flare (charge glow): 5 frames of 8 tiles per row and direction
    for kind in ("horizontal", "diagonal", "vertical"):
        rows = {"top": [], "bottom": []}
        for f in range(5):
            cv = A.Canvas(64)
            r = 3 + f * 1.2
            cv.disc(0, 0, r + 2, FX_E1)
            cv.disc(0, 0, r, FX_E2)
            cv.disc(0, 0, r * 0.6, FX_E4)
            ent = [A.OamEntry(-16, -8, 32, 16, 0, 0, 0, 0)]
            sh = A.TileSheet(64)
            sh.cut(cv, ent, overwrite=True)
            rows["top"] += sh.tiles[0:4] + [None] * 4
            rows["bottom"] += sh.tiles[32:36] + [None] * 4
        for half in ("top", "bottom"):
            out[f"projectiles/flare_{kind}_{half}.gfx"] = A.tiles_to_bytes(rows[half])
    return out


def sprite_data():
    """{file stem: CData} for src/data/sprites/*.c"""
    return {p.stem: A.parse_c([p]) for p in A.c_files("src/data/sprites/*.c")}


def sprite_blocks(sprites, sizes) -> dict:
    """{region path: bytes} for every sprite graphics / palette INCBIN."""
    out = {}
    for stem, d in sprites.items():
        frames = frames_by_anim(d)
        gfx = [(s, p) for s, (p, _) in d.incbin.items() if p.endswith(".gfx")]
        for sym, path in gfx:
            size = sizes.get(path[len("data/"):])
            if not size:
                continue
            ntiles = size // 32
            sheet = A.TileSheet(SPRITE_FIRST_TILE + max(ntiles, 64) + 64)
            paint(sheet, frames, d.oam,
                  lambda cv, a, i, n, e, stem=stem: draw_sprite_frame(cv, stem, a, i, n, e),
                  SPRITE_FIRST_TILE, SPRITE_FIRST_TILE + ntiles)
            out[path[len("data/"):]] = A.tiles_to_bytes(sheet.tiles[SPRITE_FIRST_TILE:SPRITE_FIRST_TILE + ntiles])
        for sym, (path, _) in d.incbin.items():
            if path.endswith(".pal"):
                size = sizes.get(path[len("data/"):])
                if not size:
                    continue
                rows = max(1, size // 32)
                cols = []
                for r in range(rows):
                    cols += creature_palette(stem + sym, r % 4)
                out[path[len("data/"):]] = A.pal_bytes(cols)[:size]
    return out


def apply_spritesets(rom, regions, layout) -> int:
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
    return len(SPRITESETS)


def build(sizes) -> dict:
    fx = effects_data()
    sprites = sprite_data()
    sheet = common_sheet(fx, sprites)
    out = {
        "hud/common.gfx": A.tiles_to_bytes(sheet.tiles[COMMON_FIRST_TILE:COMMON_FIRST_TILE + COMMON_TILES]),
        "hud/common.pal": A.pal_bytes([c for e in COMMON_ENERGY for c in A.fx_palette(e)]),
    }
    out.update(beam_blocks(fx))
    out.update(sprite_blocks(sprites, sizes))
    return out


def apply(rom: bytearray, regions, layout) -> list[str]:
    by_path = {r.path: r for r in regions}
    sizes = {r.path: r.size for r in regions}
    n = 0
    for path, data in build(sizes).items():
        r = by_path.get(path)
        if r is None:
            continue
        data = data[:r.size]
        rom[r.addr:r.addr + r.size] = data + bytes(r.size - len(data))
        n += 1
    k = apply_spritesets(rom, regions, layout)
    return [f"sprites/effects: {n} blocks, {k} spritesets"]


def main():
    import argparse
    from inventory import load_regions
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--sheet", help="write the common sheet as a PNG")
    ap.add_argument("--sprite", action="append", default=[], help="write <stem>.png for these sprite files")
    ap.add_argument("--out", default=".", help="directory for --sprite PNGs")
    args = ap.parse_args()
    sizes = {r.path: r.size for r in load_regions()}
    if args.sheet:
        fx = effects_data()
        sheet = common_sheet(fx, sprite_data())
        pals = [A.fx_palette(e) for e in COMMON_ENERGY]
        A.sheet_png(args.sheet, sheet.tiles[COMMON_FIRST_TILE:COMMON_FIRST_TILE + COMMON_TILES], pals, scale=3,
                    pal_of=lambda t: 1)
    for stem in args.sprite:
        d = A.parse_c([A.c_files(f"src/data/sprites/{stem}.c")[0]])
        blocks = sprite_blocks({stem: d}, sizes)
        gfx = [data for path, data in blocks.items() if path.endswith(".gfx")]
        if not gfx:
            continue
        data = gfx[0]
        tiles = [[v for b in data[i:i + 32] for v in (b & 15, b >> 4)] for i in range(0, len(data), 32)]
        pal = creature_palette(stem)
        rows = []
        for anim, frames in d.frames.items():
            rows.append([d.oam[o] for o, _ in frames if o in d.oam])
        A.frames_png(f"{args.out}/{stem}_frames.png", rows[:24],
                     lambda t: tiles[t - SPRITE_FIRST_TILE] if 0 <= t - SPRITE_FIRST_TILE < len(tiles) else None,
                     lambda p: pal)


if __name__ == "__main__":
    main()
