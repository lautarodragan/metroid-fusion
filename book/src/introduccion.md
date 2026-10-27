# Introducción

Esta es una decompilación en progreso de **Metroid Fusion** (Game Boy Advance):
código C y assembly que, al compilarse, produce un ROM idéntico byte a byte al
original.

## Progreso

El estado actualizado está en el
[README](https://github.com/lautarodragan/metroid-fusion/blob/main/README.md)
del repositorio. Al momento de escribir esto:

- 3256/3607 funciones decompiladas (90.27%, faltan 351).
- 0x5dca90/0x6f9d24 bytes de datos fuera de blobs (84.03%, faltan 0x11d294).

Hay una planilla con el progreso detallado:
<https://docs.google.com/spreadsheets/d/1HvJ-jynb-4P9tfEBVJmkQFpIg6mJRDRUBvDIBiLxQIo/>

> **Atención:** la decompilación todavía **no es shiftable** (ver
> [Shiftabilidad](shiftabilidad.md)). No la uses como base para trabajar en
> otra cosa.

## ROMs y regiones

El repositorio puede generar varios ROMs, con nombres de la forma
`mf_{region}.gba` (o `mf_{region}_debug.gba`). La región indica a qué versión
apunta el ROM:

| Región    | Versión              | Estado                                                       |
|-----------|----------------------|--------------------------------------------------------------|
| `us`      | USA, Norteamérica    | Soportada (`sha1: ca33f4348c2c05dd330d37b97e2c5a69531dfe87`) |
| `eu`      | Europa               | Todavía no soportada                                         |
| `jp`      | Japón                | Todavía no soportada                                         |
| `cn`      | China                | Todavía no soportada                                         |
| `eu_beta` | Beta europea         | Todavía no soportada                                         |

El sufijo `_debug` indica si el ROM incluye las funciones de debug; es
opcional y **todavía no está soportado**. El ROM que se genera por defecto es
`mf_us.gba`.

## Comunidad

- [Metroidret](https://discord.gg/2MGB9Xbr9y) (Discord)
- [MAGConst](https://discord.gg/WtekHKb) (Discord)
