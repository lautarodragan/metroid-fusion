# About these docs

This book is built with [mdBook](https://rust-lang.github.io/mdBook/) from the
repository's `book/` directory and is published to GitHub Pages
(<https://lautarodragan.github.io/metroid-fusion/>) every time `main`
changes.

## Current state: `docs/` and `book/`

For now several chapters **don't live in `book/`**: they are files in `docs/`
that the book includes as-is with mdBook's `\{{#include}}` directive (for
example, `book/src/docs/synthetic_check.md` only includes
`docs/synthetic_check.md`). This way the book always stays in sync with those
files.

If you want to fix one of those chapters, edit the file in `docs/`, not the
page in `book/src/docs/`.

Later on, the files in `docs/` will be consolidated into `book/src/` and
`docs/` will go away.

## Previewing locally

Install mdBook (the version CI uses is pinned in
`.github/workflows/book.yml`), for example:

```sh
cargo install mdbook --locked --version 0.5.4
```

and from the repository root:

```sh
mdbook serve book   # serves on http://localhost:3000 and reloads on edit
mdbook build book   # generates the HTML in book/book/ (ignored by git)
```
