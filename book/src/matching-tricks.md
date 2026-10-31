# Matching tricks

Most functions in the decompilation are written the way the original
programmers most likely wrote them. A few are not: no natural form has been
found that makes agbcc emit the same instructions as the original ROM, so they
contain a statement that does nothing for the game but nudges the compiler
(a no-op assignment, an empty `do { } while (0)`, a register pinned with
`asm`).

These tricks go through the `FAKE_MATCH_*` macros of
[`include/compiler_tricks.h`](https://github.com/lautarodragan/metroid-fusion/blob/main/include/compiler_tricks.h)
instead of being written inline with a comment:

- a reader immediately sees "this is a compiler-matching trick, not game
  logic";
- a typo in a comment goes unnoticed, a typo in a macro name breaks the build;
- `grep FAKE_MATCH_` lists every remaining trick.

The macros expand to exactly what was written inline before, so the ROM is
byte-identical either way.

**If you find a natural form of one of these functions that still matches,
remove the macro call** (and the include, if it was the last one in the file)
and update the list below.

## The macros

| Macro | Expands to | What it does to agbcc |
|---|---|---|
| `FAKE_MATCH_BLOCK(stmts)` | `do { stmts; } while (0)` | The extra loop level changes register allocation and the schedule of the enclosed statements |
| `FAKE_MATCH_SELF_ASSIGN(x)` | `(x) = (x)` | Forces a load and store of `x` |
| `FAKE_MATCH_NOP_OR(x)` | `(x) \|= 0` | Forces a read-modify-write of `x` |
| `FAKE_MATCH_NOP_ADD(x)` | `(x) += 0` | Makes `x` used (read and written back) at this point |
| `FAKE_MATCH_INC_DEC(x)` | `(x)++, (x)--` | Folded away, but changes how `x` is assigned to a register or how a constant is built |
| `FAKE_MATCH_DEAD_STORE(var, value)` | `(var) = (value)` | The store is removed, but evaluating `value` early changes register allocation and the constant pool |
| `FAKE_MATCH_COPY(dst, src)` | `(dst) = (src)` | An extra local used instead of `src`; it gets its own pseudo-register |
| `FAKE_MATCH_PIN_REG(type, name, reg, value)` | `register type name asm(reg) = (value); asm("" : "+r"(name))` | Forces `value` into hard register `reg` at this point |

`FAKE_MATCH_PIN_REG` is the strongest: it dictates a register instead of
nudging the allocator, so it is the one most likely to hide what the original
code looked like.

## Call sites

| Function | File | Macro |
|---|---|---|
| `Haze_Bg3` | `src/haze.c` | `FAKE_MATCH_BLOCK` (2) |
| `Haze_PowerBombExpanding` | `src/haze.c` | `FAKE_MATCH_BLOCK` |
| `Haze_PowerBombRetracting` | `src/haze.c` | `FAKE_MATCH_BLOCK` |
| `BgClipUpdateHatches` | `src/bg_clip.c` | `FAKE_MATCH_BLOCK` (2) |
| `NewFileIntroProcessHornoad` | `src/new_file_intro.c` | `FAKE_MATCH_BLOCK` + `FAKE_MATCH_NOP_ADD`, `FAKE_MATCH_NOP_ADD` |
| `SamusDraw` | `src/samus.c` | `FAKE_MATCH_SELF_ASSIGN` |
| `unk_7b674` | `src/menus/navigation_conversation.c` | `FAKE_MATCH_NOP_OR` |
| `BeamCoreXTransformationInit` | `src/sprites_AI/beam_core_x.c` | `FAKE_MATCH_INC_DEC` |
| `ProjectileBringSpriteToPowerBombCenter` | `src/projectile.c` | `FAKE_MATCH_INC_DEC` |
| `HudGenericResetHudData` | `src/hud_generic.c` | `FAKE_MATCH_DEAD_STORE` |
| `SpriteUtilMoveRidleyFireball` | `src/sprite_util.c` | `FAKE_MATCH_COPY` |
| `Sram_VerifyFile` | `src/save_file.c` | `FAKE_MATCH_PIN_REG` |

Notes on what has been tried:

- `Sram_VerifyFile`: the original copies `magicResult` to `r0` before the addition
  (`add r0, r7, #0; add r5, r5, r0`); a plain `checksumResult += magicResult`
  adds `r7` directly. Casts, other types and a separate result variable don't
  produce the copy.

## Not tricks

Some code looks odd but is believed to be faithful to the original, so it does
not use these macros: the dead clamp in `PauseScreenInit`, the BUGFIX-guarded
wrong extern in `sa_x.c`, the redundant `status |= SPRITE_STATUS_MOSAIC` in
BOX 2, idioms such as `MOD_AND` and `<< 24 >> 26`, and the `asm` block in
`dma.c`. Multi-statement macros wrapped in `do { } while (0)` (in `sprite.c`
and `ending.c`) are the usual C idiom, not a trick.

## Lint

`tools/check_tricks.py` (run in CI) fails if `src/` or `include/` contains a
raw empty `asm("")`, a `register ... asm(...)` variable, a `|= 0` / `+= 0` /
`-= 0` / `^= 0`, a self-assignment, an `x++, x--`, or a `while (0)` outside a
`#define`. It cannot recognize dead stores or extra copies, so those rely on
review.
