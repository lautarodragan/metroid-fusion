# Struct layout

Many structs have bytes that no code ever reads or writes: holes left by the
compiler for alignment, or fields that the original declared but never used.
They are written with the macros of
[`include/struct_layout.h`](https://github.com/lautarodragan/metroid-fusion/blob/main/include/struct_layout.h)
(included by `types.h`) instead of `unk_*` / `padding*` fields, so that the
layout stays byte-identical while the reader sees at a glance that nothing uses
these bytes.

| Macro | Expands to | Use |
|---|---|---|
| `UNUSED(n)` | `unsigned char _unused_<line>[n]` | `n` bytes the original declared (not explained by alignment) that no code accesses |
| `PADDING(n)` | `unsigned char _padding_<line>[n]` | Explicit padding by design: a filler up to a fixed size (`SaveFile`, `SramHeader`), or the offset of an overlay struct (`IntroTextTilesFade`) |
| `UNUSED_BITS(type, n)` | `type : n` | `n` never-accessed bits of a bit-field unit (an unnamed bit-field) |
| `STATIC_ASSERT(cond)` | `typedef char _static_assert_<counter>[(cond) ? 1 : -1]` | Compile-time check, fails with "size of array ... is negative" |
| `ASSERT_OFFSET(type, member, offset)` | `STATIC_ASSERT` on the offset of `member` | Pins where a member is |
| `ASSERT_SIZE(type, size)` | `STATIC_ASSERT` on `sizeof(type)` | Pins the size of a struct |

The names of the `UNUSED`/`PADDING` members come from `__LINE__`, so two of them
can't be on the same line. `STATIC_ASSERT` uses `__COUNTER__` instead: agbcc
rejects a redefined typedef, and two headers of a translation unit could assert
on the same line number. None of these emit code or data.

## The rule

For each never-accessed field or gap (check every use first: the C code, the
assembly of `asm/` that accesses audio structs by offset, overlay structs and
pointer arithmetic, and the tools and tests that read RAM by offset; a copy of
the whole struct doesn't count as an access):

1. **Alignment**: if the bytes are exactly what the compiler inserts by itself
   (before an aligned member, or at the end of the struct), delete them and let
   the compiler pad. agbcc aligns every struct and union to 4 bytes and rounds
   its size up to a multiple of 4, so a struct member always starts on a
   multiple of 4, and `struct { u8 a; }` is 4 bytes. Right after the struct,
   add `ASSERT_OFFSET` for the member that follows the removed bytes and
   `ASSERT_SIZE`.
2. **Unused**: if the gap can't be explained by alignment, the original
   declared something there: use `UNUSED(n)` (or `PADDING(n)` when it is
   clearly explicit padding by design).
3. **Ambiguous**: an alignment-sized gap that could also be an unused `u16`
   (or similar) is deleted, with assertions, as in 1.
4. Deliberate size arrays (`u8 size[1344]` in `union NonGameplayRam`) and
   blobs used only for a whole-struct copy (`struct NavConversationPopUpInfo`,
   `struct BslDiagramInfo`) stay as they are.

Example (`struct EndingData`): `samusOamPriority` is at 0x9D and the pointer
`pSamusOamFrame` must be at 0xA0, so the two bytes in between are alignment:

```c
    u8 samusOamPriority;            // 0x9D
    u16* pSamusOamFrame;            // 0xA0
    ...
};

ASSERT_OFFSET(struct EndingData, pSamusOamFrame, 0xA0);
ASSERT_SIZE(struct EndingData, 0x2B0);
```

When a field turns out to be used, give it a real name instead (and remove the
assertion if it was only there for the gap). Since the Makefile has no header
dependencies, run `make tidy` before checking a header change.
