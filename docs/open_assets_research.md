# Investigación: "base ROM abierta" con assets originales

> Estado: investigación de baja prioridad + prototipo mínimo (`tools/open_assets/`).
> Nada de lo que se describe acá necesita, lee ni descarga la ROM de Nintendo.
> Las reglas de clean room de [CONTRIBUTING.md](../CONTRIBUTING.md) siguen aplicando.
> **No es asesoramiento legal.** La sección 3 resume principios generales para
> decidir si vale la pena seguir; ante cualquier distribución pública conviene
> consultar a un abogado.

## 0. Resumen

- **Qué se busca:** reemplazar `mf_us_baserom.gba` por un archivo generado por
  nosotros (contenido propio o procedural, bajo CC0 o similar) para que
  `tools/extractor.py` lo consuma igual que a la ROM original y `make` produzca
  una ROM que arranque y se pueda jugar con gráficos, sonido, texto y niveles
  de relleno.
- **Factibilidad técnica:** alta para "compila y genera una ROM", media para
  "arranca sin colgarse" y baja-media para "jugable de punta a punta". El
  extractor solo copia `size` bytes desde `addr` para 3492 regiones, así que
  una "base ROM abierta" es simplemente un archivo de 8 MiB con contenido válido
  en esas posiciones. El prototipo ya genera uno (con LZ77 y RLE válidos,
  verificados por decodificación) y el extractor lo consume sin errores.
- **Bloqueantes principales:**
  1. El build **no es shiftable** (lo dice el README; hay 684 direcciones ROM
     literales en `src/`). Cada reemplazo debe entrar en **exactamente** el
     tamaño de la región original. Arte original más complejo que el original
     puede no comprimir dentro de ese presupuesto.
  2. **48 regiones `Blob_*` (1,11 MiB, 18 %)** no están entendidas; varias tienen
     punteros absolutos (voicegroups de audio, tablas de punteros a texto) y la
     de texto (496 KiB) contiene todos los idiomas.
  3. Gran parte del contenido expresivo **no está en la base ROM sino en el
     repo**: 661 secuencias de música (`sound/tracks/*.s`), ~37 300 entradas OAM
     (3 984 frames de sprites), ubicación de enemigos, puertas, eventos, demos.
     Una ROM "100 % sin material de Nintendo" requiere reemplazar eso también.
  4. **Legal:** una base ROM abierta resuelve el problema de los *assets*, pero
     no el del *código*: la decompilación sigue siendo una obra derivada del
     programa de Nintendo (ver §3).
- **Próximo paso recomendado:** fase A (§4): conseguir agbcc en un entorno
  controlado, compilar con la base ROM abierta del prototipo, correrla en mGBA
  (BIOS HLE) y anotar dónde se cuelga. En paralelo, armar el harness de
  emulación (§4.4), que sirve también para tests con la ROM real.

## 1. Inventario de `database.json`

`database.json` es una lista de 3492 entradas `{path, dir?, addr.us, count,
size}`. El extractor escribe `count * size` bytes desde `addr` en
`<dir|data>/<path>`. `size` es el tamaño del elemento (1 = bytes, 2 = paletas
u16, 4 = streams u32, y valores raros como 20-58 que son tamaños de frame de
SA-X); no afecta el formato del contenido.

Tabla generada con `python3 tools/open_assets/inventory.py`:

| Categoría | Tipo | Regiones | Bytes | KiB | % |
|---|---|---:|---:|---:|---:|
| `sound_sample`: muestras DirectSound (header WaveData + PCM s8) | asset | 385 | 1 762 059 | 1720,8 | 27,1 % |
| `gfx_lz`: gráficos 4bpp comprimidos LZ77 | asset | 210 | 1 544 128 | 1507,9 | 23,8 % |
| `blob`: regiones no entendidas (`Blob_*`) | lógica/mixto | 48 | 1 168 020 | 1140,6 | 18,0 % |
| `gfx_raw`: gráficos 4bpp sin comprimir (sprites, HUD, proyectiles…) | asset | 161 | 727 776 | 710,7 | 11,2 % |
| `gfx_samus`: tiles por frame de Samus/SA-X (conteos en C) | asset | 866 | 294 528 | 287,6 | 4,5 % |
| `room_bg_rle`: layouts BG0/1/2 de salas (RLE de sala) | layout | 844 | 282 897 | 276,3 | 4,4 % |
| `font`: glifos de texto (`text_characters.gfx`) | asset | 1 | 196 608 | 192,0 | 3,0 % |
| `tileset_metatiles`: bloque 16x16 -> 4 entradas de tile (`tilesets/*.tm`) | layout | 63 | 192 116 | 187,6 | 3,0 % |
| `tilemap_lz`: tilemaps comprimidos LZ77 (pantallas, BG3/BG0 de salas, `.tt.lz`) | asset | 144 | 163 362 | 159,5 | 2,5 % |
| `palette`: paletas BGR555 | asset | 378 | 84 384 | 82,4 | 1,3 % |
| `room_clipdata_rle`: capa de colisión/comportamiento (RLE de sala) | lógica | 387 | 61 082 | 59,7 | 0,9 % |
| `misc`: `rooms/background_empty.bin`, `new_file_intro/space_map_bg` | lógica | 2 | 8 764 | 8,6 | 0,1 % |
| `tilemap_raw`: `logo.tt`, `common_tilemap.tt`, `door_transition.tm.rle` | asset | 3 | 6 272 | 6,1 | 0,1 % |
| **total extraído** | | **3492** | **6 491 996** | **6339,8** | 100 % |

Agregado por tipo: assets puros 73,6 % (4,56 MiB), layout de niveles 7,3 %,
lógica/estructura (clipdata + blobs + misc) 19,1 %.

Notas:

- No hay gráficos RLE "de BIOS": los `.rle` usan el RLE propio del juego
  (`RoomRleDecompress`, `src/room.c`). Todo lo comprimido de gráficos/tilemaps es
  LZ77 de BIOS (`LZ77UncompVram`/`LZ77UncompWram`, 23 llamadas en `src/`).
- No hay regiones de "datos de música" extraídas: las secuencias ya están en el
  repo como asm (ver §1.2). Sí se extraen las muestras PCM y los voicegroups (en
  un blob).
- Las tablas de punteros y de animación casi no aparecen en `database.json`:
  ya están definidas en C (ver §1.2). Las que quedan están dentro de blobs.
- Solo `Blob_79bec0_79c128.bin` (616 B) no tiene ningún `INCBIN` que lo
  consuma (`inventory.py` lo reporta); habría que confirmar si se incluye por
  otro camino o si es un hueco.
- El pedido original hablaba de 47 blobs; `database.json` tiene **48**
  (incluyendo dos con dirección sin prefijo `0x`, p. ej. `Blob_5766D4_5766e0`),
  y su suma (0x11d294) coincide con la cifra del README.

### 1.1 Las 48 regiones `Blob_*`

Agrupadas por el archivo que las incluye (`inventory.py --blobs` da el detalle):

| Grupo (consumidor) | Blobs | Bytes | Qué es probablemente / riesgo con placeholder |
|---|---:|---:|---|
| `src/data/text_data.c` (`0x6B2FAC`) | 1 | 507 700 | Strings de todos los idiomas (u16 por carácter, códigos de control en `include/constants/text.h`; `CHAR_TERMINATOR = 0xFF00`). Los punteros de monólogos (`src/new_file_intro.c`) apuntan **adentro** de este blob con direcciones literales. |
| `src/data/new_file_intro_data.c` | 12 | 411 888 | Datos de cinemáticas de intro (probablemente gráficos/tilemaps/OAM sin separar). Riesgo medio. |
| `src/new_file_intro.c` | 5 | 9 840 | Incluye `0x79C5C0` = tablas `sMessageTextPointers`/`sLocationTextPointers` (punteros absolutos a strings). Con ceros, el texto leería desde la dirección 0. |
| `src/data/sa_x_close_up.c` | 1 | 79 490 | Datos de la cinemática del primer plano de SA-X. |
| `src/data/menus/pause_screen_misc_data.c` | 6 | 44 926 | Pantalla de pausa / mapas (el de 44 302 B probablemente datos de minimapa). |
| `src/data/sram_pointers.c` | 1 | 37 188 | Desconocido (¿datos por defecto de guardado?). |
| tilesets (`tilesets_set1/4/7.c`, `common_pals.c`) | 11 | 33 608 | Están pegados a `sTileset_N_Tilemap`; probablemente más tilemaps de tileset o datos animados sin separar. |
| sprites (`generic_data.c`, `sprite_data.c`, `sprites/target.c`, `sprites/omega_metroid.c`) | 4 | 22 404 | Tablas de sprites (posiblemente con punteros). |
| `src/data/audio.c` (`0xA5710`) | 1 | 13 772 | **Voicegroups** de m4a (entradas de 12 bytes = `struct Voice`, con puntero absoluto a la muestra). Las pistas los referencian con `.word 0x80a5710` etc. |
| `src/data/ending_data.c` | 4 | 6 320 | Datos del final/créditos. |
| `src/text.c` | 1 | 268 | Desconocido (tabla de texto). |
| sin consumidor | 1 | 616 | `Blob_79bec0_79c128`. |
| **total** | **48** | **1 168 020** | |

Para la base ROM abierta, cada blob necesita una de tres estrategias:
(a) entenderlo y moverlo a C/formato conocido (lo que de todos modos busca la
decomp), (b) un relleno "seguro" específico (el prototipo lo hace para
voicegroups, texto y tablas de punteros a texto), o (c) ceros, aceptando el
riesgo. En el GBA leer la dirección 0 no hace "segfault" (devuelve el open bus
de la BIOS), así que los modos de falla típicos son **bucles infinitos**
(esperando un terminador), **saltos a punteros a función nulos** (= reset de
BIOS, bucle de reinicio) y **DMA con tamaños basura**.

### 1.2 Lo que ya está en C/asm (no se extrae)

Según el README, hay 0x6f9d24 bytes de datos en total; 6 491 996 se extraen,
así que unos **~803 KiB de datos ya están definidos en el repo**:

| Dato | Dónde | Tipo |
|---|---|---|
| Secuencias de música y SFX (661 archivos, ~143 600 líneas `.byte`) y tabla de 747 sonidos | `sound/tracks/*.s`, `sound/sound_entries.s` (generados desde la ROM con `tools/trackExtractor.py`) | asset (composición) |
| Frames OAM de sprites/Samus/menús: ~37 300 `OAM_ENTRY` en ~3 984 frames | `src/data/sprites/*.c`, `src/data/samus/*`, menús | asset/layout (forma del sprite) |
| Tablas de animación y punteros (frames, timers, gráficos por frame de Samus con conteos de tiles) | `frame_data_pointers.c`, `sprite_pointers.c`, `samus_graphics.c`, `samus_animation_pointers.c` | estructura |
| Cabeceras de sala (`RoomEntryRom`: tileset, props de BG, música, efectos…), 394 salas | `src/data/rooms_data.c` | lógica/layout |
| Ancho/alto de cada capa RLE, tamaño BGCNT de cada BG3 LZ77 | `src/data/rooms/**/*.c` (bytes antes del `INCBIN`) | estructura |
| Enemigos por sala (spritesets), puertas/conexiones, eventos, demos (inputs grabados) | `rooms/**/*.c`, `connection_data.c`, `event_data.c`, `demo_data.c` | lógica/level design |
| Física de Samus, tablas de IA (p. ej. velocidades de salto de Hornoad), proyectiles, partículas, haze, scroll | `samus_data.c`, `sprites/*.c`, `projectile_data.c`, `particle_data.c`, `haze_data.c`, `scroll_data.c` | lógica |
| Tablas de comportamiento de clipdata y bloques | `clipdata_data.c`, `block_data.c` | lógica |
| Motor de sonido m4a y código aún no decompilado (~45 000 líneas) | `asm/*.s` | código |

Consecuencia: la base ROM abierta reemplaza ~73 % "assets puros" de lo
extraído, pero **la música, la forma de los sprites (OAM) y el diseño de niveles
de alto nivel (puertas, enemigos, eventos) seguirían siendo los originales**
salvo que también se reemplacen en el repo (ver §3 y fase C).

## 2. Formatos y qué necesita un reemplazo

Restricción transversal: mientras el build no sea shiftable, **cada reemplazo
debe medir exactamente lo mismo que la región** (el extractor copia tamaños
fijos y los arrays de C tienen tamaño explícito; un `INCBIN` más grande no
compila y cambiar el tamaño del array corre todas las direcciones siguientes,
rompiendo los 684 punteros literales). Más chico se puede: se rellena con
ceros y se pierde el espacio.

| Categoría | Formato | Qué necesita un reemplazo válido | Procedural | A mano |
|---|---|---|---|---|
| `gfx_lz` | Header u32 `0x10 \| (tamaño << 8)`, bloques con byte de flags MSB-first; referencia = 2 bytes (largo 3-18, distancia 1-4096). | Stream LZ77 válido **≤ tamaño de región** que descomprima a un tamaño que no pise memoria vecina (destino VRAM/EWRAM; el tamaño original no se conoce sin la ROM, hay que inferirlo del código consumidor). Para VRAM, **ninguna referencia con distancia 1** (la BIOS escribe de a 16 bits). | Fácil (el prototipo lo hace). | Medio: arte 4bpp/16 colores; el presupuesto comprimido limita la complejidad. |
| `gfx_raw`, `gfx_samus`, `font` | Tiles 4bpp de 8x8 (32 bytes, nibble bajo = píxel izquierdo). Para Samus/SA-X los conteos de tiles por fila están en C. | Exactamente el mismo tamaño. Los índices de tile deben coincidir con lo que usan los frames OAM en C (tile N de la hoja = parte del sprite). | Trivial (relleno), medio si se quiere que "se vea la silueta" (se puede rasterizar desde los `OAM_ENTRY` del C). | Alto: cientos de sprites y 866 frames de Samus/SA-X. |
| `palette` | u16 BGR555 (bit 15 ignorado), filas de 16; índice 0 transparente. | Mismo tamaño; para paletas animadas/fades el código interpola, cualquier valor es válido. | Trivial. | Fácil. |
| `tilemap_lz` | LZ77 de entradas u16 de BG (tile 10 bits, flip H/V, paleta 4 bits). Para BG de salas el tamaño de BG (BGCNT) está en C justo antes del stream. | Stream ≤ región, que descomprima a 0x800/0x1000/0x2000 según BGCNT. Las regiones más chicas (252 B) solo admiten mapas casi uniformes. | Fácil. | Medio (diseño de pantallas). |
| `tilemap_raw` | `.tt` (tablas de tiles; formato a confirmar), `door_transition.tm.rle` (RLE de sala tipo 0, con byte de tamaño inicial). | Mismo tamaño. | Fácil. | Fácil. |
| `tileset_metatiles` | u16 inicial + 4 entradas u16 por bloque de 16x16 (`room.c` usa `pTilemap + 1`). | Mismo tamaño; referenciar tiles existentes del tileset. | Fácil. | Medio. |
| `room_bg_rle` | RLE propio en dos pasadas (byte bajo, luego byte alto de cada u16); cada pasada: modo 1 = contadores de 8 bits, si no 16 bits; bit alto del contador = repetir. Ancho/alto en C. | Exactamente `ancho*alto` bloques; stream ≤ región. Hay capas de 12 bytes (vacías) que solo admiten "todo igual" en modo 16 bits. | Fácil. | Alto (diseño de niveles), y limitado por presupuesto. |
| `room_clipdata_rle` | Igual que arriba; valores = `enum Clipdata` (`CLIPDATA_SOLID = 16`, pendientes, puertas, ascensores…). | Coherente con puertas (`connection_data.c`), posiciones de spawn, enemigos y BG1. Si no, Samus cae fuera de la sala o queda trabada. | Medio (cajas/pisos); coherencia con puertas requiere leer C. | Alto. |
| `sound_sample` | WaveData de MP2K: `u16 tipo, u16 estado (0x4000 = loop), u32 frecuencia*1024, u32 inicio de loop, u32 nº de muestras`, luego PCM s8. (Layout estándar del motor; confirmar contra `src/audio.c`.) | Header coherente con el tamaño. | Trivial (onda cuadrada/seno/ruido) o síntesis aditiva/FM simple. | Medio: grabar/sintetizar 385 instrumentos/SFX bajo licencia libre. |
| Voicegroups (blob `0xA5710`) | `struct Voice` de 12 bytes: tipo, tecla base, largo, pan/sweep, puntero a muestra o a onda CGB, envolvente ADSR. Keysplits (tipo 0x40) apuntan a sub-tablas. | Punteros válidos a muestras (direcciones fijas, se pueden calcular desde `database.json`). | Fácil (el prototipo apunta todo a la muestra 0). | Medio. |
| Música (`sound/tracks/*.s`) | Secuencias m4a/"Sappy" con los macros de `sound/m_play_def.s`. | Pistas nuevas en el mismo formato, misma cantidad de entradas en `sound_entries.s`. No hay límite de tamaño fijo duro si se reemplaza todo el bloque de pistas en asm, pero los datos que siguen se correrían: hay que verificar si algo apunta con dirección literal después de esa zona. | Medio: generar MIDI procedural y convertir (falta un conversor tipo mid2agb, o escribir uno). | Alto: 661 pistas. |
| Texto (blob `0x6B2FAC` + punteros) | u16 por carácter con códigos de control (`0xFC00` flecha, `0xFD00` página nueva, `0xFE00` salto de línea, `0xFF00` fin). `charmap.txt` todavía está vacío. | Strings en las direcciones exactas que apuntan las tablas (o reescribir las tablas, que están en un blob). | Fácil para "todo vacío"; medio para textos de relleno legibles (requiere mapear el charset). | Medio (redacción + 6-7 idiomas). |
| Blobs restantes | Desconocido. | Entenderlos o rellenar con algo seguro. | — | — |

## 3. Análisis legal (encuadre general, no asesoramiento)

### 3.1 Assets vs. código

- El derecho de autor protege **expresión**, no ideas, métodos ni mecánicas
  (EE. UU.: 17 U.S.C. §102(b); UE: Directiva 2009/24/CE art. 1.2 para software;
  en Argentina la Ley 11.723 sigue la misma lógica general). Gráficos, música
  (composición y grabaciones/muestras), texto y probablemente el diseño de
  niveles (selección y disposición) son obras protegidas. Tablas puramente
  funcionales (física, velocidades, tablas de seno) tienen protección débil o
  nula por falta de originalidad, pero **en conjunto** pueden integrar la
  expresión del programa; no conviene asumir que "los datos son libres".
- Una base ROM hecha de assets **creados por nosotros** (o generados por
  código propio) es obra nuestra y podemos licenciarla libremente. Esto resuelve
  la dependencia de la ROM comercial **para los assets**.
- **El código es otra historia.** Una decompilación *matching* reproduce, por
  diseño, el comportamiento y la forma del programa compilado de Nintendo; por
  más que se escriba "fresco" (como pide CONTRIBUTING.md, que prohíbe mirar
  código filtrado), se obtiene estudiando el binario, y el resultado es
  plausiblemente una **obra derivada** del programa. La metodología de clean room
  clásica (Phoenix BIOS) separa a quien analiza de quien implementa y solo
  transfiere especificaciones; acá eso no ocurre.
- Excepciones relevantes y sus límites:
  - EE. UU.: *Sega v. Accolade* (9th Cir. 1992) y *Sony v. Connectix* (9th Cir.
    2000) consideraron *fair use* la copia **intermedia** durante ingeniería
    inversa para lograr interoperabilidad, con un producto final no infractor.
    Distribuir una reimplementación casi idéntica del mismo juego no es el caso
    analizado en esos fallos.
  - UE: el art. 6 de la Directiva 2009/24/CE permite decompilar para la
    interoperabilidad de un programa *creado independientemente*, y prohíbe
    usar la información para un programa "sustancialmente similar".
  - DMCA §1201 (EE. UU.) y equivalentes: el GBA no tiene cifrado; el logo del
    header es otro tema (abajo).
- Además del código C, el repo ya contiene **datos expresivos derivados de la
  ROM** fuera de la base ROM (música en `sound/tracks`, frames OAM, diseño de
  salas en C). Hoy tienen el mismo estatus que el código; una variante "open"
  debería poder compilarse sin ellos (fase C).
- **Conclusión práctica:** la base ROM abierta (a) elimina la necesidad de
  conseguir una ROM para compilar/testear, (b) permite distribuir **los assets**
  con licencia libre y (c) habilita CI con screenshots sin material de Nintendo
  en los artefactos *de datos*. **No** convierte en libre al binario resultante:
  distribuir la ROM compilada (que contiene el código derivado) sigue siendo
  riesgoso. Recomendación: no publicar ROMs compiladas; publicar solo el
  generador de assets y, como hoy, el código fuente.
- Los precedentes de tolerancia (Nintendo no ha atacado los repos de
  decompilación tipo pret, aunque sí actuó contra distribuciones de ports/binarios
  y ROM hacks con contenido propio) son **de facto, no de iure**.

### 3.2 Marcas

- "Metroid", "Metroid Fusion", "Samus", el logo del título y el nombre
  "Nintendo" son marcas. El riesgo de marca aparece al **presentar** el producto
  (título, logo, nombre del archivo, descripción), no por el código en sí.
- En el header de la ROM, el Makefile pone `GAME_TITLE = METROID4USA` y
  `GAME_CODE = AMTE`. Para una variante "open" conviene un título y código
  propios (p. ej. una variable `OPEN_ASSETS=1` que cambie `GAME_TITLE`/`GAME_CODE`)
  y que el arte/texto de relleno no use los nombres ni el logo.
- `tools/gbafix` (GPLv3, de devkitPro) copia el **logo de Nintendo** que la BIOS
  real exige para arrancar. *Sega v. Accolade* consideró que usar un mecanismo
  de bloqueo basado en una marca no le da al titular un derecho a excluir
  (en EE. UU.); todo el homebrew de GBA hace lo mismo. Para CI en emulador con
  BIOS HLE (mGBA) el logo no se verifica, así que una build "open" podría
  dejarlo vacío y eliminar el tema por completo en artefactos de test (a
  verificar empíricamente que mGBA arranque sin logo).
- Nunca usar la BIOS de Nintendo: mGBA trae BIOS HLE, que también implementa
  `LZ77UnComp*`.

### 3.3 Precedentes de "motor + assets libres"

| Proyecto | Motor | Assets libres | Lección |
|---|---|---|---|
| **Freedoom** | Doom (código liberado por id bajo GPL) | IWAD completo bajo BSD-3 | El caso ideal: código libre + assets libres = juego 100 % distribuible. El IWAD es *drop-in*, igual que nuestra base ROM. |
| **OpenTTD + OpenGFX/OpenSFX/OpenMSX** | Reimplementación que nació de ingeniería inversa/decompilación de TTD | Gráficos, sonidos y música GPLv2 | Muy parecido a este caso: los sets libres permiten jugar sin el juego original, pero el código siempre tuvo el antecedente de la decompilación (tolerado de facto). Los sets libres se hicieron respetando el layout de sprites del original para ser *drop-in*. |
| **OpenRCT2** | Reimplementación desde el binario de RCT2 | Requiere todavía (en gran parte) los assets originales; existen proyectos de reemplazo parcial | Muestra cuánto cuesta cubrir el 100 % de assets de un juego comercial. |
| **LibreQuake, OpenArena, FreeDM** | Quake/Quake III/Doom (GPL) | Assets libres | Mismo patrón que Freedoom. |
| **Homebrew GBA** (devkitPro/libtonc/butano) | Código propio | Assets propios | Las herramientas libres (gbafix, grit, mid2agb-like) y el uso del logo en el header son práctica estándar. |
| Ports de decomps de N64 (sm64, OoT/Ship of Harkinian) | Decompilación | **No** distribuyen assets: los extraen de la ROM del usuario | Es el modelo actual de este repo. La base ROM abierta agregaría la opción "sin ROM". |

### 3.4 Licencias sugeridas

- **CC0-1.0** para todo lo generado proceduralmente y para el generador de
  datos (o MIT, como el repo). Máxima compatibilidad; el prototipo declara CC0
  para su salida.
- Para arte/música aportados a mano: **CC0** (preferido, sin fricción) o
  **CC-BY 4.0** / **CC-BY-SA 4.0** si los autores quieren atribución/copyleft.
  CC-BY-SA 4.0 es compatible en un solo sentido con GPLv3; mezclar con MIT está
  bien siempre que los assets queden como archivos separados con su licencia.
- Evitar CC-NC/ND (no son libres y complican la redistribución en CI).
- Fuentes tipográficas: dibujar una propia o usar una pixel font CC0/OFL; con
  OFL hay que respetar sus condiciones de nombre reservado.
- Registrar procedencia: cada asset con autor, licencia y "no derivado de
  material de Nintendo" (un `ASSETS_LICENSE.md`/manifest), y prohibir explícitamente
  trazar sobre capturas del juego original.

## 4. Plan por fases

### 4.0 Prototipo incluido (`tools/open_assets/`)

- `inventory.py`: categorías y tamaños desde `database.json` + qué archivo de
  `src/`/`sound/` consume cada región (genera las tablas de §1).
- `formats.py`: encoder/decoder LZ77 compatible con BIOS y seguro para VRAM
  (sin referencias de distancia 1), encoder/decoder del RLE de salas (elige 8 o
  16 bits por pasada), paletas/tiles/ondas de relleno.
- `make_open_baserom.py -o open_baserom.gba`: genera el archivo de 8 MiB. Lee
  de C el tamaño BGCNT de cada BG LZ77 y el ancho/alto de cada capa RLE; genera
  salas "caja" (o piso/techo si no entra), voicegroups apuntando a una muestra
  válida, texto lleno de terminadores y tablas de punteros a texto apuntando a
  un terminador; valida todo decodificándolo. Nunca sobrescribe un archivo
  existente sin `--force`.
- `test_formats.py`: tests de ida y vuelta (`python3 tools/open_assets/test_formats.py`).

Resultado actual: las 3492 regiones reciben contenido; 209 de los 210
`gfx_lz` entran con 2 KiB descomprimidos (uno solo con 256 B), los 144
`tilemap_lz` entran con el tamaño BGCNT esperado; 122 capas de clipdata solo
admiten "piso y techo" (no caja completa) por presupuesto; `tools/extractor.py`
consume el archivo sin cambios y produce los 3492 archivos (6 491 996 bytes).
**No se compiló ni se ejecutó la ROM** (no hay agbcc en este entorno y no se
instaló código externo).

### 4.1 Fase A: "arranca a algo" (estimado: 3-10 días)

1. Compilar con la base ROM abierta (`cp open_baserom.gba mf_us_baserom.gba;
   python3 tools/extractor.py && make`). Esperable: compila igual que con la
   ROM real (los tamaños son idénticos); `make check` obviamente falla.
2. Ejecutar en mGBA con BIOS HLE y trazar: ¿llega al título? ¿la intro
   termina? Probables puntos de cuelgue: blobs de intro/cinemáticas
   (`new_file_intro_data.c`, 412 KiB), texto, pausa/minimapa, sram.
3. Para cada cuelgue: entender el blob (avanza la decomp) o darle un relleno
   seguro. Atajo aceptable: un flag de compilación (`OPEN_ASSETS`) que saltee
   intro/cinemáticas y vaya directo a una sala (código propio en el fork; no
   cambia el build matching).
4. Header propio (título/código) bajo ese flag.
5. Criterio de salida: llega a gameplay en la sala inicial sin colgarse 10 000
   frames con input aleatorio.

### 4.2 Fase B: una sala de prueba jugable (estimado: 1-3 semanas)

1. Elegir una sala chica (las salas `test*` de `rooms/test` o la primera del
   Main Deck) y generar: tileset con 4-8 bloques legibles (piso, pared, fondo,
   puerta), clipdata coherente con las puertas de `connection_data.c` y la
   posición de entrada, BG1 visible igual al clipdata.
2. Samus placeholder: rasterizar sus 866 frames **a partir de los `OAM_ENTRY`
   del C** (un rectángulo de color por pieza, con borde), de modo que cada
   animación muestre una silueta que se mueve correctamente sin copiar arte.
   Lo mismo sirve para todos los sprites (fase C).
3. Paletas legibles (alto contraste) y fuente propia mínima (dígitos + A-Z) para
   el HUD.
4. Un par de muestras sintetizadas y una pista de prueba propia en
   `sound/tracks` (opcional en esta fase).
5. Criterio de salida: test automático que entra a la sala, camina, salta,
   dispara y atraviesa una puerta, con screenshots estables.

### 4.3 Fase C: cobertura completa con placeholders (estimado: 4-8 semanas de placeholders procedurales; meses para arte "lindo")

- Todos los tilesets (63) y sus metatiles, BG3 de salas, pantallas de menú,
  título propio (sin la marca), finales.
- Clipdata de las 394 salas: generar automáticamente a partir de la geometría
  de puertas y ascensores definidos en C (cajas conectadas), garantizando que se
  pueda recorrer, o diseñar niveles nuevos (requiere build shiftable para
  salirse del presupuesto de bytes).
- Texto de relleno para todos los mensajes (requiere mapear el charset y la
  estructura del blob de texto).
- Sonido: 385 muestras sintetizadas y **reemplazo de las 661 secuencias** (por
  ejemplo, generador de melodías + conversor a macros m4a).
- Opcional para una build totalmente libre: reemplazar frames OAM/diseño de
  salas del C por versiones generadas, y hacer el build shiftable con assets en
  formatos fuente (PNG/MIDI/JSON) convertidos en build, como hacen los
  proyectos pret (`gbagfx`, `mid2agb`). Esto elimina la restricción de tamaño
  exacto, que es el mayor freno para arte original.

### 4.4 Harness de tests con emulador controlable desde Python

Requisitos: headless, avanzar frames, inyectar input, leer memoria (IWRAM/EWRAM
para variables como `gCurrentArea` = `0x0300002C`, `gCurrentRoom` =
`0x0300002D`, sacadas de `linker.ld`/`.map`), screenshots, BIOS HLE.

| Opción | Instalación | Frames / input / memoria / screenshot | Comentario |
|---|---|---|---|
| **Bindings Python oficiales de mGBA** (`mgba.core`, `mgba.image`) | No están en PyPI: compilar mGBA con `-DBUILD_PYTHON=ON` (usa cffi); Ubuntu tiene `libmgba-dev` 0.10.2 pero no el módulo Python | Sí / sí (`set_keys`) / sí (`core.memory`) / sí (`Image.to_pil()`) | La opción más directa y fiel. Costo: build en CI (cacheable). |
| **pygba** (PyPI 0.2.9, MIT) | `pip install pygba`, pero depende del módulo `mgba` de arriba | Wrapper cómodo + entorno gymnasium | Útil como referencia de API. |
| **libretro.py** (PyPI 0.12.0, Python ≥ 3.12) + core `mgba_libretro.so` | `pip install libretro.py`; el core sale de `apt install libretro-mgba` (0.10.2 en Ubuntu noble) o del wheel de stable-retro | Pensado justamente para testear cores: frames, input, memoria vía API libretro, framebuffer | Sin compilar nada; buena opción para CI. |
| **stable-retro** (PyPI 1.0.1, Farama) | `pip install stable-retro` (wheel de ~120 MB con `mgba_libretro.so` incluido) | `env.step`, RAM, observación = pantalla | Exige registrar la ROM como "integración" custom (hash + `data.json`); pensado para RL, más rígido. |
| mGBA CLI + scripting Lua (0.10+) | `apt install mgba-sdl`/`mgba-qt` | Lua puede leer memoria, sacar screenshots y controlar input | Bueno para depuración; para CI headless conviene una de las de arriba. mGBA también tiene su propio sistema de tests de regresión por screenshots ("CInema"). |

Recomendación: **libretro.py + `libretro-mgba`** para CI sin compilar el
emulador; bindings oficiales de mGBA si se necesita algo que libretro no
exponga. Esquema de test:

```python
# pseudo-código
core = load("mgba_libretro.so"); core.load_game("mf_open.gba")
for frame, keys in script:            # script = lista de (frame, botones)
    core.set_input(keys); core.run()
assert read_u8(0x0300002C) == AREA_MAIN_DECK
save_png(core.framebuffer(), f"out/{frame}.png")   # comparar con golden PNG (tolerancia)
```

Los "golden" se generan con la ROM abierta, por lo que pueden versionarse en el
repo sin material de Nintendo. El mismo harness corre localmente con la ROM real
para tests de comportamiento (sin commitear sus screenshots).

## 5. Esfuerzo y riesgos

| Trabajo | Estimado |
|---|---|
| Prototipo de generador (hecho) | ~1 día |
| Fase A (boot) | 3-10 días, dominado por cuántos blobs hay que entender |
| Harness Python + CI | 2-4 días |
| Fase B (sala jugable + Samus por OAM) | 1-3 semanas |
| Fase C placeholders procedurales completos | 4-8 semanas |
| Fase C con arte/música originales de calidad | meses, depende de colaboradores |
| Build shiftable + assets en formatos fuente | semanas a meses (es también un objetivo de la decomp) |

Riesgos:

1. **Presupuesto de bytes fijo** por región mientras no haya build shiftable:
   limita arte/niveles originales; el placeholder simple sí entra.
2. **Blobs desconocidos** con punteros o estructuras que el código asume
   (bucles infinitos/saltos nulos). Mitigación: avanzar la decomp de esas
   zonas; rellenos específicos; flag para saltear cinemáticas.
3. **Tamaños de descompresión desconocidos** para `gfx_lz` (no se pueden leer
   sin la ROM): elegir tamaños conservadores y validar con el código consumidor
   (destinos en VRAM/EWRAM) para no pisar memoria.
4. **Coherencia de nivel**: clipdata/puertas/enemigos/eventos tienen que
   concordar; con datos inconsistentes el juego no "crashea" pero queda
   injugable.
5. **Legal**: la base ROM abierta no cambia el estatus del código ni del
   contenido derivado que ya está en el repo (música, OAM, layout de salas). No
   distribuir ROMs compiladas; mantener nombres/logo fuera de los assets.
6. **Contaminación**: aportes de arte "inspirado" que en realidad trazan o
   reproducen sprites del original. Mitigación: manifest de procedencia y
   revisión; preferir generación procedural.
7. **Mantenimiento**: cada vez que la decomp separa un blob en regiones nuevas,
   el generador debe aprender el formato (el inventario lo detecta: categoría
   nueva o región sin generador).
