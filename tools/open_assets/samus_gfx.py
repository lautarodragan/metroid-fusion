"""Placeholder graphics for Samus: a suited figure with an arm cannon.

Samus' graphics are streamed every frame (TransferSamusGraphics in
src/in_game.c): the current animation frame (``struct SamusAnimData`` in
src/data/samus/samus_graphics.c) names a "top" block (body, OBJ tiles 0.. of
the first two tile rows), a "bottom" block (legs, tiles 20.. of the same rows)
and an OAM frame that places 8x8..32x32 pieces of those rows on screen. The
arm cannon is separate: the arm cannon direction picks a 6x2 tile block
(tile rows 2-3, ``sArmCannonGfxPointers_*``) and the arm cannon animation
(``struct ArmCannonAnimData``) places three 16x16 pieces of it.

For every animation frame this module

1. works out the pose from the animation's name (running, spinning, morph
   ball, crouching, aim direction, facing side...) and the frame number,
2. draws a figure on a canvas in Samus-local coordinates, fitted to the area
   the frame's OAM pieces cover (head at the top of the pieces, feet at the
   bottom), with the arm cannon arm left out when the frame has separate arm
   cannon pieces,
3. cuts the canvas through the frame's OAM entries into the tiles of the
   frame's top/bottom blocks.

Each graphics block is drawn from the frame that shows most of its tiles.
The arm cannon blocks are drawn as a cannon pointing in their direction,
laid out like the pieces the arm cannon frames place for that direction.

All palettes Samus uses (suits, charge/speed/screw/save flashes, freeze,
death fade...) are derived from one semantic 16-colour layout (see PAL_*).

The figures are procedural placeholders, drawn so that emulator tests and
screenshots of the open ROM show a readable pose.

    python3 tools/open_assets/samus_gfx.py --preview out.png   # contact sheet
"""

from __future__ import annotations

import argparse
import math
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import oam_art as A  # noqa: E402

# ---------------------------------------------------------------------------
# Palette layout (index -> role). Body (OBJ row 0) and arm cannon (row 1)
# use the same layout.
# ---------------------------------------------------------------------------

OUTLINE = 1
SUIT_D, SUIT_M, SUIT_L = 2, 3, 4          # suit
ACC_D, ACC_M, ACC_L = 5, 6, 7             # armour plates (shoulders, knees, boots)
VIS_D, VIS_M, VIS_L = 8, 9, 10            # visor
MET_D, MET_M, MET_L = 11, 12, 13          # arm cannon metal
GLOW, WHITE = 14, 15

SUITS = {
    # name: (suit dark, suit light, plate dark, plate light)
    "Fusion": ("#1d3f6e", "#8ec5f0", "#a04a10", "#ffc35a"),
    "Varia": ("#6e2410", "#ff9a5a", "#7a5a10", "#ffe27a"),
    "Gravity": ("#3c1d6e", "#c49af0", "#14506e", "#7ae2ff"),
    "SaX": ("#3a3f48", "#c8ccd4", "#5a1010", "#e85a5a"),
}


def suit_palette(suit: str = "Fusion"):
    sd, sl, ad, al = (A.hexrgb(c) for c in SUITS[suit])
    suit_r = A.ramp(sd, sl, 3)
    acc_r = A.ramp(ad, al, 3)
    return [(0, 0, 0), A.hexrgb("#0c0c18"), *suit_r, *acc_r,
            A.hexrgb("#0e5a2c"), A.hexrgb("#2ed060"), A.hexrgb("#c8ffd0"),
            A.hexrgb("#3a3a4a"), A.hexrgb("#8a8aa0"), A.hexrgb("#e0e0f0"),
            A.hexrgb("#fff27a"), (255, 255, 255)]


def tint(pal, color, t: float, keep_outline: bool = True):
    color = A.hexrgb(color) if isinstance(color, str) else color
    out = [pal[0]]
    for i, c in enumerate(pal[1:], 1):
        out.append(c if (i == OUTLINE and keep_outline) else A.mix(c, color, t))
    return out


def palette_for(name: str, n_colors: int) -> bytes:
    """Colours for the Samus palette array ``name`` (``sSamusPal_*``)."""
    suit = next((s for s in SUITS if s in name), "Fusion")
    base = suit_palette(suit)
    rows = max(1, n_colors // 16)
    out = []
    for r in range(rows):
        t = r / max(1, rows - 1)
        if "Flashing" in name:
            p = tint(base, "#ffffff", 0.75)
        elif "ScrewAttacking" in name:
            p = tint(base, "#40ff70", 0.45 if r == 0 else 0.25)
        elif "Speedboost" in name:
            p = tint(base, "#5ab4ff", 0.35 + 0.25 * ("1" in name))
        elif "DyingFade" in name:
            p = tint(base, "#ffffff", t, keep_outline=False)
        elif "Dying" in name:
            p = tint(base, "#ffffff", 0.3)
        elif "Frozen" in name:
            p = tint(base, "#9ae8ff", 0.6)
        elif "AbsorbX" in name:
            p = tint(base, "#ffe060", 0.5 * math.sin(math.pi * t))
        elif "Charging" in name:
            beam = {"Ice": "#9ae8ff", "Wave": "#d070ff", "Plasma": "#70ff90",
                    "Wide": "#ff70d0", "Charge": "#ffffa0"}.get(
                next((b for b in ("Ice", "Wave", "Plasma", "Wide", "Charge") if b in name), ""), "#ffffff")
            p = tint(suit_palette(list(SUITS)[(r // 4) % 4]), beam, 0.15 * (r % 4))
        elif "SavingGame" in name:
            p = tint(base, "#ffffff", 0.2 * (r % 4))
        elif "LoadingSave" in name:
            m = re.search(r"_(\d+)$", name)
            k = int(m.group(1)) if m else 0
            p = tint(base, "#ffffff", max(0.0, 1 - k / 26))
        elif "Row1" in name or "Unused" in name:
            p = base
        else:
            p = base
        out += p
    return A.pal_bytes(out[:n_colors] + [(0, 0, 0)] * max(0, n_colors - len(out)))


# ---------------------------------------------------------------------------
# Pose classification
# ---------------------------------------------------------------------------

AIMS = ("DiagonalUp", "DiagonalDown", "Forward", "Up", "Down", "None", "Default", "Sideways", "Upwards")


def classify(anim: str) -> dict:
    """Pose info from an animation name like sSamusAnim_Running_Forward_Left."""
    n = anim.split("_", 1)[1] if anim.startswith("s") and "_" in anim else anim
    parts = n.split("_")
    side = 1 if "Right" in parts else -1
    aim = next((a for a in AIMS if a in parts), "None")
    pose = parts[0]
    return {"pose": pose, "aim": aim, "side": side, "name": n}


SPIN = {"Spinning", "SpaceJumping", "ScrewAttacking", "StartingWallJump"}
BALL = {"MorphBall", "Morphing", "Unmorphing", "PullingIntoMorphFromHanging"}
FRONT = {"Turning", "TurningMidAir", "TurningAndCrouching", "FacingForeground", "OnSavePad", "Saving", "OnNavigationPad", "DownloadingAbility",
         "BeingRecharged", "UsingElevator", "LoadingSave", "Dying", "UnlockingSecurity",
         "UnlockingHabitationsDeck", "HangingOnVerticalLadder", "ArmOutOnVerticalLadder",
         "ShootingOnVerticalLadder", "StartingToHoldArmOutOnVerticalLadder",
         "StartingToPutArmAwayOnVerticalLadder"}
BACK = {"FacingBackground"}
HANG = {"HangingOnLedge", "LoweringDownToStartHanging", "PullingUpFromHanging",
        "PullingForwardFromHanging", "MovingOnHorizontalLadder", "TurningOnHorizontalLadder",
        "ShootingOnHorizontalLadder", "AfterShootingOnHorizontalLadder"}
CROUCH = {"Crouching", "TurningAndCrouching", "ShootingAndCrouching"}
AIR = {"MidAir", "TurningMidAir", "StartingSpinJump", "HitByOmegaMetroid"}


# ---------------------------------------------------------------------------
# Figure drawing
# ---------------------------------------------------------------------------

def bbox(entries):
    if not entries:
        return None
    return (min(e.x for e in entries), min(e.y for e in entries),
            max(e.x + e.w for e in entries), max(e.y + e.h for e in entries))


def leg_ik(hip, foot, a, b, bend):
    """Knee position for a two-bone leg, the knee bending toward ``bend``."""
    hx, hy = hip
    fx, fy = foot
    dx, dy = fx - hx, fy - hy
    d = math.hypot(dx, dy) or 1e-6
    if d >= a + b:
        k = a / (a + b)
        return hx + dx * k, hy + dy * k
    # distance along hip->foot to the knee projection and its offset
    x = (a * a - b * b + d * d) / (2 * d)
    h = math.sqrt(max(0.0, a * a - x * x))
    ux, uy = dx / d, dy / d
    px, py = -uy, ux                  # perpendicular
    if px * bend < 0:
        px, py = -px, -py
    return hx + ux * x + px * h, hy + uy * x + py * h


def draw_leg(cv, hip, knee, foot, s, front):
    shade = SUIT_M if front else SUIT_D
    cv.capsule(*hip, *knee, 3.4, shade, 3.0)
    cv.capsule(*knee, *foot, 3.0, shade, 2.8)
    cv.disc(knee[0] + s * 0.6, knee[1], 2.2, ACC_M if front else ACC_D)
    # boot
    cv.ellipse(foot[0] + s * 1.6, foot[1] - 1.2, 3.8, 2.3, ACC_M if front else ACC_D)
    if front:
        cv.set(round(foot[0] + s * 2.5), round(foot[1] - 2.5), ACC_L)


def draw_head(cv, hx, hy, s, view="side", look=0.0):
    cv.disc(hx, hy, 5.6, SUIT_M, shade=(SUIT_L, SUIT_D))
    if view == "side":
        vx, vy = hx + s * 2.6, hy + 0.3 + look
        cv.ellipse(vx, vy, 3.1, 2.1, VIS_M)
        cv.set(round(vx + s * 0.5), round(vy - 1), VIS_L)
        cv.set(round(vx - s * 1.6), round(vy + 1), VIS_D)
    elif view == "front":
        cv.ellipse(hx, hy + 0.5, 4.0, 2.0, VIS_M)
        cv.set(round(hx - 2), round(hy), VIS_L)
        cv.set(round(hx + 2), round(hy + 1), VIS_D)
    else:  # back of the helmet
        cv.ellipse(hx, hy + 2.5, 3.5, 1.2, SUIT_D)


def draw_cannon_arm(cv, x0, y0, angle, length=13.0, armed=False):
    """Upper arm + cannon from the shoulder (x0, y0) along ``angle``."""
    ca, sa = math.cos(angle), math.sin(angle)
    x1, y1 = x0 + ca * length, y0 + sa * length
    cv.capsule(x0, y0, x1, y1, 4.2, MET_M, 3.6)
    cv.capsule(x0 + ca * 2 - sa * 1.5, y0 + sa * 2 + ca * 1.5 - 1.5,
               x1 - ca * 3 - sa * 1.5, y1 - sa * 3 + ca * 1.5 - 1.5, 1.0, MET_L)
    # muzzle
    mx, my = x1 - ca * 1.5, y1 - sa * 1.5
    cv.disc(mx, my, 2.6, MET_D)
    cv.disc(mx + ca * 0.8, my + sa * 0.8, 1.3, GLOW if armed else MET_D)
    if armed:  # opened tip
        for sgn in (-1, 1):
            cv.capsule(mx - sa * 3.2 * sgn, my + ca * 3.2 * sgn, mx + ca * 3 - sa * 3.6 * sgn,
                       my + sa * 3 + ca * 3.6 * sgn, 1.2, MET_L)
    # shoulder pad
    cv.disc(x0, y0, 4.6, ACC_M, shade=(ACC_L, ACC_D))


AIM_ANGLE = {"Forward": 0.0, "None": 0.0, "Default": 0.0, "Sideways": 0.0,
             "DiagonalUp": -math.pi / 4, "DiagonalDown": math.pi / 4,
             "Up": -math.pi / 2, "Upwards": -math.pi / 2, "Down": math.pi / 2}


def aim_angle(aim: str, s: int) -> float:
    a = AIM_ANGLE.get(aim, 0.0)
    if s < 0:
        a = math.pi - a
    return a


def skeleton(info, i, n, T, L, U):
    """Key points of a side-view figure fitted to the frame's pieces."""
    s = info["side"]
    pose = info["pose"]
    top_y = (T or U)[1]
    foot_y = (L or U)[3] - 1
    cx = ((L or U)[0] + (L or U)[2]) / 2
    # the legs get what is left under head + torso (22 px)
    hip_y = min(foot_y - 6, top_y + 22)
    leg_len = foot_y - hip_y
    lean = 1.0
    phase = 2 * math.pi * i / max(1, n)
    hip_x = cx - s * 0.5
    if pose == "Running":
        lean = 3.0
        sw = 6.5 * math.sin(phase)
        f1 = (hip_x + s * sw, foot_y - max(0.0, 5 * math.cos(phase)))
        f2 = (hip_x - s * sw, foot_y - max(0.0, -5 * math.cos(phase)))
        feet = [f2, f1]
    elif pose == "Skidding":
        lean = -2.0
        feet = [(hip_x - s * 2, foot_y), (hip_x + s * 7, foot_y)]
    elif pose in CROUCH or pose == "Landing" or leg_len < 14:
        feet = [(hip_x - s * 4, foot_y), (hip_x + s * 5, foot_y)]
    elif pose in AIR or pose.startswith("Getting"):
        lean = -1.5 if pose == "HitByOmegaMetroid" else 1.0
        feet = [(hip_x - s * 3, foot_y), (hip_x + s * 4, foot_y - 6)]
    elif pose.startswith("Shinesparking") or pose.startswith("DelayAfterShinesparking"):
        lean = 5.0 if info["aim"] == "Sideways" else 0.0
        feet = [(hip_x - s * 4, foot_y), (hip_x - s * 1, foot_y - 2)]
    else:
        feet = [(hip_x - s * 3.5, foot_y), (hip_x + s * 3.5, foot_y)]
    neck = (hip_x + s * lean, hip_y - 10)
    return {"s": s, "hip_x": hip_x, "hip_y": hip_y, "foot_y": foot_y, "leg_len": leg_len,
            "feet": feet, "neck": neck, "phase": phase,
            "shoulder": (neck[0] + s * 2.5, neck[1] + 2)}


def draw_humanoid(cv, info, i, n, T, L, U, cannon_separate):
    sk = skeleton(info, i, n, T, L, U)
    s, pose = sk["s"], info["pose"]
    hip_x, hip_y, feet, leg_len, phase = sk["hip_x"], sk["hip_y"], sk["feet"], sk["leg_len"], sk["phase"]
    a = b = 9.5
    neck = sk["neck"]
    head = (neck[0] + s * 0.5, neck[1] - 6)
    # back arm (behind everything)
    sh_b = (neck[0] - s * 2, neck[1] + 2)
    swing = -math.sin(phase) * 5 if pose == "Running" else 0
    hand_b = (sh_b[0] - s * 2 + s * swing, sh_b[1] + 9)
    cv.capsule(*sh_b, *hand_b, 2.6, SUIT_D, 2.2)
    cv.disc(*hand_b, 2.2, ACC_D)
    # legs (back first)
    for k, foot in enumerate(feet):
        hip = (hip_x + (-s if k == 0 else s) * 1.5, hip_y)
        knee = leg_ik(hip, foot, a * leg_len / 19 if leg_len > 19 else a, b, s)
        draw_leg(cv, hip, knee, foot, s, front=k == 1)
    # torso
    cv.capsule(hip_x, hip_y - 1, *neck, 5.2, SUIT_M, 5.6)
    cv.capsule(neck[0] + s * 1.8, neck[1] + 1.5, neck[0] + s * 1.2, neck[1] + 5, 1.6, SUIT_L)
    cv.capsule(hip_x - 4, hip_y, hip_x + 4, hip_y, 1.3, ACC_D)  # belt
    cv.disc(sh_b[0], sh_b[1] - 0.5, 3.6, ACC_D)
    look = -1.0 if info["aim"] in ("Up", "DiagonalUp") else 1.0 if info["aim"] in ("Down", "DiagonalDown") else 0.0
    draw_head(cv, *head, s, look=look)
    if not cannon_separate:
        ang = aim_angle(info["aim"], s) if info["aim"] not in ("None", "Default") else (
            math.pi / 2 - s * 0.5 if pose not in AIR else math.pi / 2 - s * 1.0)
        draw_cannon_arm(cv, *sk["shoulder"], ang, length=11)


def draw_front(cv, info, i, n, T, L, U, view="front"):
    top_y = U[1]
    foot_y = U[3] - 1
    cx = (U[0] + U[2]) / 2
    hip_y = min(foot_y - 6, top_y + 22)
    neck = (cx, hip_y - 10)
    head = (cx, neck[1] - 6)
    pose = info["pose"]
    arms_up = pose in ("HangingOnVerticalLadder", "UsingElevator") or "Ladder" in pose
    for sgn in (-1, 1):
        hip = (cx + sgn * 2.5, hip_y)
        foot = (cx + sgn * 4, foot_y)
        knee = leg_ik(hip, foot, 9.5, 9.5, sgn)
        cv.capsule(*hip, *knee, 3.3, SUIT_M, 3.0)
        cv.capsule(*knee, *foot, 3.0, SUIT_M, 2.8)
        cv.disc(knee[0], knee[1], 2.0, ACC_M)
        cv.ellipse(foot[0] + sgn, foot[1] - 1.2, 3.2, 2.2, ACC_M)
    cv.capsule(cx, hip_y - 1, *neck, 5.6, SUIT_M, 6.0)
    cv.capsule(cx - 4, hip_y, cx + 4, hip_y, 1.3, ACC_D)
    for sgn in (-1, 1):
        sh = (cx + sgn * 6, neck[1] + 2)
        hand = (sh[0] + sgn * 2, sh[1] - 10) if arms_up else (sh[0] + sgn * 1.5, sh[1] + 9)
        cv.capsule(*sh, *hand, 2.8 if sgn > 0 else 3.6, MET_M if sgn < 0 else SUIT_M, 2.4 if sgn > 0 else 3.4)
        cv.disc(*sh, 3.8, ACC_M, shade=(ACC_L, ACC_D))
        if view == "front":
            cv.disc(*hand, 2.2, ACC_D if sgn > 0 else MET_D)
    if view == "front":
        cv.capsule(cx - 1, neck[1] + 2, cx - 1, neck[1] + 6, 1.4, SUIT_L)
    else:  # backpack
        cv.rect(cx - 3, neck[1] + 1, cx + 3, neck[1] + 7, SUIT_D)
    draw_head(cv, *head, 1, view=view)


def draw_spin(cv, info, k, U):
    s = info["side"]
    cx, cy = (U[0] + U[2]) / 2, (U[1] + U[3]) / 2
    w, h = U[2] - U[0], U[3] - U[1]
    # axis: horizontal / vertical boxes, otherwise a diagonal alternating per frame
    if w > h + 4:
        axis = 0.0
    elif h > w + 4:
        axis = math.pi / 2
    else:
        axis = math.pi / 4 if k % 2 == 0 else -math.pi / 4
    # head end goes round in the spin direction
    head_end = 1 if (k // 2) % 2 == 0 else -1
    if s < 0:
        head_end = -head_end
    L = min(max(w, h), 32) / 2 - 1.5          # half length along the axis
    ca, sa = math.cos(axis) * head_end, math.sin(axis) * head_end
    px, py = -sa * s, ca * s                    # "belly" side of the curl
    hx, hy = cx + ca * (L - 5.5), cy + sa * (L - 5.5)
    kx, ky = cx - ca * (L - 4), cy - sa * (L - 4)
    # back (outer arc) and tucked legs (inner side)
    cv.capsule(hx - px * 1.5, hy - py * 1.5, kx - px * 1.5, ky - py * 1.5, 5.5, SUIT_M)
    cv.capsule(cx - px * 3.5 + ca * 2, cy - py * 3.5 + sa * 2, kx - px * 3, ky - py * 3, 2.0, SUIT_L)
    cv.capsule(kx, ky, cx + px * 3.5 + ca * 2, cy + py * 3.5 + sa * 2, 3.2, SUIT_D)      # shins
    cv.disc(kx + px * 0.5, ky + py * 0.5, 3.6, ACC_M, shade=(ACC_L, ACC_D))               # knees
    cv.ellipse(cx + px * 4 + ca * 2.5, cy + py * 4 + sa * 2.5, 3.2, 2.2, ACC_D, angle=axis)  # boots
    cv.disc(hx, hy, 5.6, SUIT_M, shade=(SUIT_L, SUIT_D))                                  # helmet
    vx, vy = hx + px * 2.4 + ca * 1.0, hy + py * 2.4 + sa * 1.0
    cv.ellipse(vx, vy, 3.0, 2.0, VIS_M, angle=axis + math.pi / 2)
    cv.set(round(vx + ca), round(vy + sa), VIS_L)
    if info["pose"] == "ScrewAttacking":
        for t in range(0, 360, 30):
            a = math.radians(t + 15 * k)
            cv.set(round(cx + math.cos(a) * (L - 0.5)), round(cy + math.sin(a) * (L - 0.5)), GLOW)


def draw_ball(cv, info, k, U, frac=1.0):
    cx, cy = (U[0] + U[2]) / 2, (U[1] + U[3]) / 2
    r = max(4.0, min(U[2] - U[0], U[3] - U[1]) / 2 - 1.2)
    cx, cy = cx, U[3] - 1 - r
    cv.disc(cx, cy, r, SUIT_M, shade=(SUIT_L, SUIT_D))
    a = math.radians(45 * k)
    for sgn in (-1, 1):
        cv.line(cx + math.cos(a) * r * 0.9 * sgn, cy + math.sin(a) * r * 0.9 * sgn,
                cx + math.cos(a) * 1.5 * sgn, cy + math.sin(a) * 1.5 * sgn, ACC_D)
    cv.disc(cx, cy, 2.0 if r > 5 else 1.4, GLOW)
    cv.set(round(cx - r * 0.45), round(cy - r * 0.5), WHITE)


def draw_frame(cv, info, i, n, entries, cannon_separate):
    body = [e for e in entries if e.tile < 64]
    U = bbox(body)
    if U is None:
        return
    T = bbox([e for e in body if e.tile % 32 < 20])
    L = bbox([e for e in body if e.tile % 32 >= 20])
    pose = info["pose"]
    m = re.search(r"Frame(\d+)", info.get("gfx", ""))
    k = int(m.group(1)) if m else i
    if pose in SPIN or (pose == "StartingSpinJump" and False):
        draw_spin(cv, info, k, U)
    elif pose in BALL and (pose == "MorphBall" or (U[3] - U[1]) <= 18):
        draw_ball(cv, info, k, U)
    elif pose in FRONT:
        draw_front(cv, info, i, n, T, L, U)
    elif pose in BACK:
        draw_front(cv, info, i, n, T, L, U, view="back")
    else:
        draw_humanoid(cv, info, i, n, T, L, U, cannon_separate)
    cv.outline(OUTLINE)


# ---------------------------------------------------------------------------
# Arm cannon blocks
# ---------------------------------------------------------------------------

def cannon_layout_key(entries):
    x0 = min(e.x for e in entries)
    y0 = min(e.y for e in entries)
    return tuple(sorted((e.tile, e.w, e.h, e.flip, e.x - x0, e.y - y0) for e in entries))


def draw_cannon_block(cv, entries, aim, side, armed, shoulder=None):
    """Cannon from the shoulder along ``aim``, as far as ``entries`` reach."""
    ang = aim_angle(aim, side)
    ca, sa = math.cos(ang), math.sin(ang)
    cells = set()
    for e in entries:
        for y in range(e.y, e.y + e.h):
            for x in range(e.x, e.x + e.w):
                cells.add((x, y))
    if shoulder is None:
        xs = [c[0] for c in cells]
        ys = [c[1] for c in cells]
        shoulder = ((min(xs) + max(xs)) / 2 - ca * 10, (min(ys) + max(ys)) / 2 - sa * 10)
    x0, y0 = shoulder
    inside = [t for t in range(-6, 48) if (round(x0 + ca * t), round(y0 + sa * t)) in cells]
    if not inside:
        return
    t0, t1 = max(min(inside), -2), max(inside) - 3
    draw_cannon_arm(cv, x0 + ca * t0, y0 + sa * t0, ang, length=max(6, t1 - t0), armed=armed)
    cv.outline(OUTLINE)


# ---------------------------------------------------------------------------
# Building all blocks
# ---------------------------------------------------------------------------

def load():
    return A.parse_c(A.c_files("src/data/samus/*.c"))


def anim_pairs(d):
    """(body anim, arm cannon anim or None) for every pointer table pair."""
    pairs = {}
    for t, body in d.pointers.items():
        if not t.startswith("sSamusAnimPointers_"):
            continue
        cann = d.pointers.get("sArmCannonAnimPointers_" + t[len("sSamusAnimPointers_"):], [])
        for k, b in enumerate(body):
            c = cann[k] if k < len(cann) else None
            if c is not None and c in d.structs:
                pairs.setdefault(b, set()).add(c)
            else:
                pairs.setdefault(b, set())
    return pairs


def gfx_region(d, sym):
    v = d.incbin.get(sym)
    if not v:
        return None
    path, lead = v
    return path[len("data/"):], lead


def build(d=None) -> tuple[dict, dict]:
    """Returns ({region path: bytes}, debug info)."""
    d = d or load()
    pairs = anim_pairs(d)
    # cannon present per body anim frame
    cannon_frames = {}
    for b, cs in pairs.items():
        for c in cs:
            for i, it in enumerate(d.structs[c]):
                if d.oam.get(it.get("pOam")):
                    cannon_frames.setdefault((b, i), True)
    candidates = defaultdict(list)    # region symbol -> [(coverage, anim, frame idx)]
    for anim, frames in d.structs.items():
        if not anim.startswith("sSamusAnim_"):
            continue
        frames = [f for f in frames if f.get("pOam") and f.get("pTopGfx")]
        for i, f in enumerate(frames):
            entries = d.oam.get(f["pOam"], [])
            for key, base in (("pTopGfx", 0), ("pBottomGfx", 20)):
                g = gfx_region(d, f[key])
                if not g:
                    continue
                n1, n2 = (g[1] + [0, 0])[:2]
                want = {base + c for c in range(n1)} | {32 + base + c for c in range(n2)}
                shown = {t for e in entries for _, _, t in e.tiles()} & want
                # prefer animations named like the block (a block is drawn
                # for its own pose even when other poses reuse it)
                match = classify(anim)["pose"] in f[key]
                candidates[f[key]].append((match, len(shown), -len(entries), anim, i))
    out = {}
    drawn = {}
    for sym, cands in candidates.items():
        cands.sort(key=lambda c: (-c[0], -c[1], c[2], c[3], c[4]))
        _, _, _, anim, i = cands[0]
        frames = [f for f in d.structs[anim] if f.get("pOam") and f.get("pTopGfx")]
        f = frames[i]
        key = (anim, i)
        if key not in drawn:
            info = classify(anim)
            info["gfx"] = f["pTopGfx"]
            cv = A.Canvas(160)
            draw_frame(cv, info, i, len(frames), d.oam[f["pOam"]], cannon_frames.get(key, False))
            sheet = A.TileSheet(128)
            sheet.cut(cv, [e for e in d.oam[f["pOam"]] if e.tile < 64], overwrite=True)
            drawn[key] = sheet
        sheet = drawn[key]
        path, lead = gfx_region(d, sym)
        n1, n2 = (lead + [0, 0])[:2]
        base = 0 if sym == f["pTopGfx"] else 20
        tiles = [sheet.tiles[base + c] for c in range(n1)] + [sheet.tiles[32 + base + c] for c in range(n2)]
        out[path] = A.tiles_to_bytes(tiles)
    out.update(build_cannon(d))
    return out, {"drawn": len(drawn)}


CANNON_FAMILY = (("OnVerticalLadder", ("VerticalLadder",)), ("OnHorizontalLadder", ("HorizontalLadder",)),
                 ("Default", ()))
ACD_AIM = {"ACD_NONE": "Forward", "ACD_FORWARD": "Forward", "ACD_DIAGONAL_UP": "DiagonalUp",
           "ACD_DIAGONAL_DOWN": "DiagonalDown", "ACD_UP": "Up", "ACD_DOWN": "Down"}


def build_cannon(d) -> dict:
    # most common piece layout per (family, aim, side)
    layouts = defaultdict(lambda: defaultdict(int))
    examples = {}
    body_of = {}
    for b, cs in anim_pairs(d).items():
        for c in cs:
            body_of.setdefault(c, b)
    for name, items in d.structs.items():
        if not name.startswith("sArmCannonAnim_"):
            continue
        info = classify(name)
        fam = next(f for f, keys in CANNON_FAMILY if not keys or any(k in name for k in keys))
        aim = {"None": "Forward", "Default": "Forward"}.get(info["aim"], info["aim"])
        for i, it in enumerate(items):
            o = d.oam.get(it.get("pOam"))
            if not o or any(e.tile < 64 or e.tile > 0x6f for e in o):
                continue
            k = cannon_layout_key(o)
            layouts[(fam, aim, info["side"])][k] += 1
            x0 = min(e.x for e in o)
            y0 = min(e.y for e in o)
            ek = (fam, aim, info["side"], k)
            examples.setdefault(ek, (o, []))
            shoulder = None
            b = body_of.get(name)
            if b:
                frames = [f for f in d.structs[b] if f.get("pOam") and f.get("pTopGfx")]
                if i < len(frames):
                    body = [e for e in d.oam.get(frames[i]["pOam"], []) if e.tile < 64]
                    U = bbox(body)
                    if U:
                        T = bbox([e for e in body if e.tile % 32 < 20])
                        L = bbox([e for e in body if e.tile % 32 >= 20])
                        shoulder = skeleton(classify(b), i, len(frames), T, L, U)["shoulder"]
            if shoulder:
                examples[ek][1].append((shoulder[0] - x0, shoulder[1] - y0))
    out = {}
    for ptab, syms in d.pointers.items():
        m = re.match(r"sArmCannonGfxPointers_(Default_Armed|Default|OnVerticalLadder|OnHorizontalLadder)_(Left|Right)_(Top|Bottom)$", ptab)
        if not m:
            continue
        fam = "Default" if m.group(1).startswith("Default") else m.group(1)
        armed = m.group(1) == "Default_Armed"
        side = 1 if m.group(2) == "Right" else -1
        # the pointer table lists one block per ACD in enum order
        for acd, sym in zip(ACD_AIM, syms):
            aim = ACD_AIM[acd]
            lk = (fam, aim, side) if layouts.get((fam, aim, side)) else ("Default", aim, side)
            lay = layouts.get(lk)
            if not lay:
                continue
            k = max(lay, key=lay.get)
            entries, sh = examples[lk + (k,)]
            shoulder = None
            if sh:
                ex0 = min(e.x for e in entries)
                ey0 = min(e.y for e in entries)
                xs = sorted(v[0] for v in sh)
                ys = sorted(v[1] for v in sh)
                shoulder = (xs[len(xs) // 2] + ex0, ys[len(ys) // 2] + ey0)
            cv = A.Canvas(160)
            draw_cannon_block(cv, entries, aim, side, armed, shoulder)
            sheet = A.TileSheet(128)
            sheet.cut(cv, entries, overwrite=True)
            g = gfx_region(d, sym)
            if not g:
                continue
            row = 64 if m.group(3) == "Top" else 96
            out[g[0]] = A.tiles_to_bytes(sheet.tiles[row:row + 6])
    return out


def palettes(d=None) -> dict:
    """{region path: bytes} for every sSamusPal_* region."""
    d = d or load()
    out = {}
    for sym, (path, _) in d.incbin.items():
        if sym.startswith("sSamusPal_"):
            out[path[len("data/"):]] = sym
    return out


def apply(rom: bytearray, regions, layout) -> list[str]:
    d = load()
    gfx, info = build(d)
    by_path = {r.path: r for r in regions}
    n = 0
    for path, data in gfx.items():
        r = by_path.get(path)
        if r is None:
            continue
        data = data[:r.size]
        rom[r.addr:r.addr + r.size] = data + bytes(r.size - len(data))
        n += 1
    npal = 0
    for path, sym in palettes(d).items():
        r = by_path.get(path)
        if r is None:
            continue
        rom[r.addr:r.addr + r.size] = palette_for(sym, r.size // 2)
        npal += 1
    return [f"samus: {n} graphics blocks ({info['drawn']} frames drawn), {npal} palettes"]


# ---------------------------------------------------------------------------
# Preview
# ---------------------------------------------------------------------------

def compose(canvas_rgb, W, x0, y0, entries, sheet_tiles, pal):
    """Draw OAM ``entries`` at (x0, y0) using tiles from ``sheet_tiles``."""
    for e in entries:
        for dx, dy, t in e.tiles():
            px = sheet_tiles.get(t)
            if px is None:
                continue
            for y in range(8):
                for x in range(8):
                    c = px[y * 8 + x]
                    if not c:
                        continue
                    sx = 7 - x if e.flip & 1 else x
                    sy = 7 - y if e.flip & 2 else y
                    X, Y = x0 + e.x + dx + sx, y0 + e.y + dy + sy
                    if 0 <= X < W and 0 <= Y < len(canvas_rgb) // (3 * W):
                        i = (Y * W + X) * 3
                        canvas_rgb[i:i + 3] = bytes(int(v) for v in pal[e.palette * 16 + c])


def preview(path: str, anims=None, scale: int = 3):
    d = load()
    gfx, _ = build(d)
    pal = suit_palette() * 2
    pairs = anim_pairs(d)
    names = anims or [a for a in d.structs if a.startswith("sSamusAnim_") and "Unused" not in a]
    cell = 64
    cols = 12
    rows_out = []
    for a in names:
        frames = [f for f in d.structs[a] if f.get("pOam") and f.get("pTopGfx")]
        cann = next(iter(pairs.get(a, ())), None)
        rows_out.append((a, frames, cann))
    # one row per animation, frames left to right
    W = cols * cell
    H = len(rows_out) * cell
    img = bytearray(bytes((40, 44, 56)) * (W * H))
    info_side = {}
    for r, (a, frames, cann) in enumerate(rows_out):
        info = classify(a)
        for i, f in enumerate(frames[:cols]):
            tiles = {}
            for key, base in (("pTopGfx", 0), ("pBottomGfx", 20)):
                g = gfx_region(d, f[key])
                if not g or g[0] not in gfx:
                    continue
                n1, n2 = (g[1] + [0, 0])[:2]
                data = gfx[g[0]]
                idx = [base + c for c in range(n1)] + [32 + base + c for c in range(n2)]
                for j, t in enumerate(idx):
                    b = data[j * 32:(j + 1) * 32]
                    tiles[t] = [v for byte in b for v in (byte & 15, byte >> 4)]
            centries = []
            if cann and i < len(d.structs[cann]):
                centries = d.oam.get(d.structs[cann][i].get("pOam"), [])
                aim = {"None": "Forward", "Default": "Forward"}.get(classify(cann)["aim"], classify(cann)["aim"])
                side = "Right" if info["side"] > 0 else "Left"
                for half, row in (("Top", 64), ("Bottom", 96)):
                    sym = f"sArmCannonGfx_Default_{side}_{half}_{aim}"
                    g = gfx_region(d, sym)
                    if g and g[0] in gfx:
                        data = gfx[g[0]]
                        for j in range(6):
                            b = data[j * 32:(j + 1) * 32]
                            tiles[row + j] = [v for byte in b for v in (byte & 15, byte >> 4)]
            ox, oy = i * cell + cell // 2, r * cell + cell - 10
            body = d.oam.get(f["pOam"], [])
            behind = cann and d.structs[cann] and False
            compose(img, W, ox, oy, body, tiles, pal)
            compose(img, W, ox, oy, centries, tiles, pal)
    if scale > 1:
        big = bytearray()
        for y in range(H):
            row = bytearray()
            for x in range(W):
                row += img[(y * W + x) * 3:(y * W + x) * 3 + 3] * scale
            big += bytes(row) * scale
        img, W, H = big, W * scale, H * scale
    write_png(path, W, H, bytes(img))
    print(f"wrote {path}: {len(rows_out)} animations")


def write_png(path, w, h, rgb):
    import struct
    import zlib

    def chunk(tag, data):
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)
    raw = b"".join(b"\0" + rgb[y * w * 3:(y + 1) * w * 3] for y in range(h))
    Path(path).write_bytes(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0))
                           + chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b""))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--preview", required=True, help="write a contact sheet PNG")
    ap.add_argument("--anim", action="append", help="only these animations (regex)")
    args = ap.parse_args()
    anims = None
    if args.anim:
        d = load()
        anims = [a for a in d.structs if a.startswith("sSamusAnim_") and any(re.search(p, a) for p in args.anim)]
    preview(args.preview, anims)


if __name__ == "__main__":
    main()
