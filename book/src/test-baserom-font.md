# Text and font in the generated test baserom

The generated test baserom (`tools/open_assets/`, see
[Generated test baserom](test-baserom-research.md)) carries a readable font
and short placeholder strings, so the emulator tests and screenshots show
what each screen is doing. The code lives in `tools/open_assets/font.py`;
`make_open_baserom.py` only calls `font.apply()` after its other layouts.

## How the game stores and draws text

### Glyphs: `sCharactersGfx` (`text_characters.gfx`, 192 KiB)

- One sheet of 4bpp 8x8 tiles (32 bytes per tile, low nibble = left pixel),
  `src/data/text_data.c`. It is the only text font; there is no separate
  Japanese sheet.
- Character code `c` is a **16x16 cell**: the top half is tile `c` (plus
  tile `c + 1` when the glyph is wider than 8 px), the bottom half is 32
  tiles later, at byte `c * 32 + 0x400` (`TextDrawCharacter`,
  `src/text.c`). So codes come in rows of 64 of which only the first 32 are
  usable, and the sheet has room for 96 such rows.
- Single-byte characters are laid out like Shift-JIS bytes:
  `code = ((b & 0xE0) << 1) | (b & 0x1F)` (`PauseDebugDrawEventText`
  converts its Shift-JIS event names this way). Printable ASCII
  `0x20-0x7F` is therefore `0x40-0x5F`, `0x80-0x9F` and `0xC0-0xDF`
  (space = `0x40`, `'0'` = `0x50`, `':'` = `0x5A`, `'A'` = `0x81`,
  `'a'` = `0xC1`). The file select draws digits as `0x50 + n` and treats
  `0x5A`/`0x40` specially, which confirms it. Half-width katakana
  (`0xA0-0xDF`) land in rows 5-6.
- Codes past the width table advance 10 px and are drawn two tiles wide:
  that is where the full-width (Japanese kana/kanji) glyphs live. Where the
  accented letters of the European languages are is not known yet (their
  strings are still in a blob).
- Pixel values: 0 = background, 2 = ink, 3 = shadow; the draw routines
  recolour 2 and 3 with a `color` argument (`2 + 2 * color`,
  `3 + 2 * color`) and never touch 1. Message banners
  (`TextDrawCharacterForMessage`) and the pause debug text turn 0 into 15
  (the box colour); the others OR glyph tiles into a cleared buffer, so
  pixels past a glyph's advance overlap the next character.

### Widths: `sCharacterWidths` (game data, in C)

`src/data/menus/pause_screen_misc_data.c`, 1184 entries (codes `0-0x49F`),
read by `TextGetCharacterWidth` (10 for larger codes). For ASCII they are
proportional (space 6, `'i'` 5, `'l'` 4, `'|'` 3, digits 7, most letters 8).
A few more narrow entries at `0x39C-0x39F`, `0x3DC-0x3DF`, `0x44E`, `0x469`
and `0x48C` suggest a second Latin set; it is not used by our strings.

### Where text is shown

| Text | Drawn by | Into | Shown through |
| --- | --- | --- | --- |
| Monologues (`sMonologueText<Lang>_<N>`, 19 per language) | `SpecialCutsceneProcessMonologue` | VRAM `0x0000`, line L at tiles `L*64` (top) / `L*64+32` (bottom), 28 columns, 9 lines | BG0, map `sIntroTilemap_662804`, palette rows 12-15 (`sIntroPal_663820`). Each tile fades in: the code decrements the palette number of its map entry three times (15 → 12). |
| Subtitles over the new-file intro and ending scenes (same monologues) | `NewFileIntroProcessAdamText`, `EndingProcessAdamText` | VRAM `0xD000`/`0xD800` (2 lines, 32 columns) | BG0 (char base 2, HOFS -8), map `sIntroSamusShipFlyingTextTilemap` at `0xE000`, palette row 15 (`sPal_598a8c`, or row 15 of the scene's full palette) |
| File select header, menu, prompts, "no data" label | `FileSelectDrawText`, `FileSelectDrawFileInfo` | char base 2 (`0x8000`), 32 tiles per row: header row 0, files rows 2/4/6, menu row 12 (`0xB000`), prompts row 18 (`0xC800`); per-line tile offsets from `sFileSelectTextTileOffsets` | BG2 (`sFileSelectBg2Tilemap`), BG1 (`sFileSelectBg1Tilemap` via EWRAM), BG0 (`sFileSelectBg0Tilemap`); palette `sFileSelectBgPal` + row 0 overrides |
| Message / location banners (`sMessageTextPointers`, `sLocationTextPointers`) | `TextDisplayMessage`, `TextDrawMessageBanner`, `TextDrawLocationText` | OBJ VRAM `0x4000 + slot * 0x800`, up to 28 tiles, 2 lines | the banner sprite |
| Navigation conversations (`sNavConversationTextPointers`, `sMessageTextPointers[43+]`) | `navigation_conversation.c` | VRAM `0x7000`, 2 lines of 224 px | pause screen BG |

Other glyph sets, not touched by `font.py`: the title screen debug font
(`menus/title_screen/characters.gfx`, 24 tiles), the HUD digits
(`hud/*digits*.gfx`), the ending credits/copyright/results graphics and the
title "press start" sprite (part of `sTitleScreenObjectsGfx`). They are
ordinary graphics regions handled with the rest of the sprites/menus.

## The generated font

- Base: **Spleen 6x12** by Frederic Cambus (BSD 2-Clause), printable ASCII
  only, vendored as `tools/open_assets/third_party/spleen/spleen_6x12.py`
  with its `LICENSE` and the converter `convert_bdf.py` (input: the BDF from
  <https://github.com/fcambus/spleen>, version 2.2.0).
- `fit_glyph` places each glyph inside **its own advance width** from
  `sCharacterWidths` and the 16-row cell (bitmap rows 2-13): one free column
  for spacing, a one pixel ink shadow (colour 3) to the lower right,
  horizontally centred. Too wide glyphs first lose duplicated columns, then
  the shadow, then their emptiest inner columns.
- The whole advance is painted with colour 1 ("paper"), which the routines
  never recolour: every line of text sits on a dark band and stays readable
  over the busy placeholder backgrounds. Columns past the advance stay 0 so
  the OR-drawing never mixes neighbouring glyphs.
- Every other cell (control area, katakana, full-width rows) stays empty.

Text layers get a fixed text palette (paper, then ink/shadow pairs for
`color` 0-6: white, yellow, cyan, green, orange, pink, highlight); the
monologue rows 12-15 are the same palette faded from full (12) to faint
(15).

## Placeholder strings

All languages get the same English placeholders, written into the unused
start of the text blob (with the pointer tables that point to them):

| Table | Example |
| --- | --- |
| Monologues | `[Monologue 8: SR388 preview]`, then `{ARROW}{ARROW}`, `(next page)`, `{ARROW}`, end: scenes that wait for "more text" and scenes that only wait for the end both advance with A. The longest of three variants that fits the original region (some are only 32 characters). |
| Messages 0-20 | `[Message: security level 1]`, `[Message: missiles]` (names from `sAbilityRamValues` in `src/data/event_data.c`) |
| Messages 21-42 / 43+ | `[Banner N]` / `[Message N: Navigation]` |
| Locations | `[Location: sector 1]` (from `enum LocationText`) |
| Navigation / pause | `[Navigation briefing N]`, `[Pause text N]` |
| File select | `SELECT A FILE`, `START   COPY   ERASE`, `[Prompt: start this file?]`, `[empty file]`, `[Notice: file A damaged]` |

`font.encode()` takes printable ASCII, `\n` (`CHAR_NEW_LINE`), `{ARROW}`
(`CHAR_NEXT_PAGE_ARROW`) and `{PAGE}` (`CHAR_NEW_PAGE`), and appends the
terminator.

## `--font-from-rom` (local option)

```sh
python3 tools/open_assets/make_open_baserom.py -o mf_us_baserom.gba --font-from-rom path/to/your_baserom.gba
```

Reads only the font region (`text_characters.gfx`) from your own baserom
(checked: 8 MiB, sha1 `ca33f4348c2c05dd330d37b97e2c5a69531dfe87`) instead
of generating the open font; the strings stay the placeholders above. The
emulator references assume the open font, so screenshot tests will differ
with it. The output stays local (`*.gba` is gitignored). The copy logic is
unit-tested with a fake ROM (`tools/open_assets/test_font.py`).

## Known gaps

- Japanese/Hiragana use the same English placeholders; kana and accented
  glyphs are left empty.
- The ending dialogue table (`sEndingDialogueTextTables`) and the title intro texts
  are not filled yet.
- Spaces in the file select "no data" label and in navigation text are
  skipped by the game, leaving a gap in the paper band.
- Banner and pause screen text use their screen's (placeholder) palettes,
  not the text palette; they are not reached by the emulator tests.
