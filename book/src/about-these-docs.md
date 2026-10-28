# About these docs

This book is built with [mdBook](https://rust-lang.github.io/mdBook/) from the
repository's `book/` directory and is published to GitHub Pages
(<https://lautarodragan.github.io/metroid-fusion/>) every time `main`
changes.

## Editing

All the project documentation lives in `book/src/`: each chapter is a
Markdown file there, and `book/src/SUMMARY.md` defines the table of contents.
To add a chapter, create the file in `book/src/` and add it to
`SUMMARY.md`.

- Link to other chapters with relative links to their `.md` file (for example
  `[Shiftability](shiftability.md)`); mdBook turns them into links to the
  generated pages and warns about broken ones.
- Link to source files in the repository with full GitHub URLs
  (`https://github.com/lautarodragan/metroid-fusion/blob/main/...`), since
  only `book/src/` is published.
- Make sure `mdbook build book` finishes without warnings before opening a
  PR.

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
