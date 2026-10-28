# Shiftabilidad (pendiente)

> **Capítulo pendiente.** La documentación sobre shiftabilidad se está
> escribiendo en `docs/` (probablemente `docs/shift*.md`). Cuando ese archivo
> exista, este capítulo debe reemplazarse por una página que lo incluya, como
> las de `book/src/docs/` (por ejemplo, `book/src/docs/<archivo>.md` con
> `\{{#include ../../../docs/<archivo>.md}}`), y actualizar `SUMMARY.md`.

Por ahora, lo importante: **la decompilación todavía no es shiftable**. Es
decir, si se agrega, quita o mueve código o datos, las direcciones fijas que
todavía quedan en el código y los datos dejan de ser válidas y el ROM
resultante no funciona. No la uses como base para trabajar en otra cosa.
