# Sobre esta documentación

Este libro se arma con [mdBook](https://rust-lang.github.io/mdBook/) a partir
del directorio `book/` del repositorio y se publica en GitHub Pages
(<https://lautarodragan.github.io/metroid-fusion/>) cada vez que hay cambios en
`main`.

## Estado actual: `docs/` y `book/`

Por ahora varios capítulos **no viven en `book/`**: son archivos de `docs/`
que el libro incluye tal cual con la directiva `\{{#include}}` de mdBook (por
ejemplo, `book/src/docs/synthetic_check.md` solo incluye
`docs/synthetic_check.md`). Así el libro queda siempre sincronizado con esos
archivos.

Si querés corregir uno de esos capítulos, editá el archivo en `docs/`, no la
página de `book/src/docs/`.

Más adelante los archivos de `docs/` se van a consolidar dentro de `book/src/`
y `docs/` va a dejar de existir.

## Previsualizar localmente

Instalá mdBook (la versión que usa CI está fijada en
`.github/workflows/book.yml`), por ejemplo:

```sh
cargo install mdbook --locked --version 0.5.4
```

y desde la raíz del repositorio:

```sh
mdbook serve book   # sirve en http://localhost:3000 y recarga al editar
mdbook build book   # genera el HTML en book/book/ (ignorado por git)
```
