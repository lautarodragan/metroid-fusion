# Tests con emulador (sin la ROM de Nintendo)

Los tests de `tests/emu/` corren la ROM construida desde la **base ROM
abierta** (`tools/open_assets/`, contenido de relleno propio) en un emulador
de GBA sin ventana, manejado desde Python. No necesitan, leen ni descargan la
ROM original ni la BIOS de Nintendo, así que corren en CI.

## Requisitos

- Lo mismo que para compilar (agbcc, `binutils-arm-none-eabi`, `python3`).
- El core libretro de mGBA: `sudo apt install libretro-mgba` (Ubuntu 24.04
  trae la 0.10.2). Se busca en `/usr/lib/<arch>/libretro/mgba_libretro.so`;
  otra ruta se indica con `MGBA_LIBRETRO_CORE=/ruta/mgba_libretro.so`.
- `pytest` (`sudo apt install python3-pytest` o `pip install pytest`).

Sin el core o sin la ROM, todos los tests se marcan como *skipped* con un
mensaje que dice qué falta.

## Cómo correrlos

```sh
tests/run_emu_tests.sh                       # build limpio en un dir temporal + pytest
tests/run_emu_tests.sh -k ingame -v          # los argumentos extra van a pytest
tests/run_emu_tests.sh --no-shift            # sin la segunda corrida (ROM desplazada)
EMU_BUILD_DIR=/tmp/mf-open tests/run_emu_tests.sh   # reusar el build (incremental)
```

`run_emu_tests.sh` copia los archivos del repo (versionados y no ignorados) a
otro directorio, genera ahí la base ROM abierta y compila con
`tools/open_assets/build_open_rom.py`. **Nunca toca el árbol de trabajo**: un
`mf_us_baserom.gba` real o sintético que tengas queda intacto.

Después repite todo con la ROM de prueba de *shift* (`make SHIFT=1`,
`mf_us_shifted.gba`, ver `docs/shiftability.md`): mismo código y
datos con relleno insertado, así que casi todo cambia de dirección. Los
mismos tests (incluidas las capturas) tienen que pasar; es la prueba en
ejecución de que el build es *shiftable*, que `check_shift.py` solo verifica
estáticamente. Tarda ~70 s en total (dos builds de ~25 s y dos corridas de
~8 s).

Si ya compilaste la ROM abierta a mano, alcanza con
`python3 -m pytest tests/emu [--emu-rom ruta/mf_us.gba]`. Los tests se saltean
si el `mf_us_baserom.gba` junto a la ROM no es una base ROM abierta (tiene un
marcador al principio), porque las referencias solo valen para esa ROM.

`build_open_rom.py [--shift]` compila en dos pasadas: algunos datos de la
base ROM son direcciones del build (vector de interrupciones, tablas de
punteros) y se llenan con el ELF de la pasada anterior. Como el Makefile no
sabe que un objeto depende de los archivos que incluye con `INCBIN`, el script
borra los objetos cuyos datos cambiaron.

## Qué verifican

| Archivo | Test |
| --- | --- |
| `test_boot.py` | Los primeros 600 frames corren (PC siempre en código, contador de frames creciente). El recorrido guionado pasa por los modos en orden: intro del título → pantalla de título → selección de archivo → intro de partida nueva → mapa → juego. Sin PC inválido ni reinicios durante todo el recorrido. |
| `test_screenshots.py` | Capturas en 5 puntos (`title_intro`, `title_screen`, `file_select`, `new_file_intro`, `in_game`) comparadas con `tests/emu/reference/*.png`. Un píxel difiere si algún canal difiere en más de 24; falla si difiere más del 0,5 % de los píxeles. Al fallar se guardan `<nombre>.actual.png` y `<nombre>.diff.png` en `tests/emu/output/` (o `--emu-output` / `$MF_EMU_OUTPUT`; en CI se suben como artefacto). |
| `test_ingame.py` | En la primera sala (`gCurrentArea` = 0, `gCurrentRoom` = 0): mantener derecha aumenta `gSamusData.xPosition` e izquierda lo reduce; A hace saltar (baja `yPosition`) y Samus vuelve al piso. Determinismo: mismo estado + mismo input → mismo hash de RAM/VRAM/OAM y misma imagen; dos encendidos dan la misma RAM. |

El recorrido (`tests/emu/scenario.py`) se ejecuta una sola vez por sesión: los
tests leen lo registrado (transiciones de modo, capturas, *save states*) y los
de juego parten del estado guardado al llegar a la sala.

### Actualizar las referencias

Cuando un cambio altera la imagen a propósito (por ejemplo, otro relleno en
`make_open_baserom.py`):

```sh
tests/run_emu_tests.sh --update-references
```

Mirar los PNG nuevos y commitearlos junto con el cambio. Las referencias solo
muestran arte de relleno generado por nosotros, así que se pueden versionar.

## Determinismo

- Opciones del core fijas en el harness (BIOS HLE, sin *frameskip*, sin
  corrección de color ni mezcla entre frames, sin optimización de *idle
  loops*), independientes de cualquier configuración local.
- Directorio de sistema/guardado vacío y temporal: nunca se carga una BIOS ni
  un `.sav` del usuario. La SRAM arranca vacía en cada encendido.
- Metroid Fusion no tiene RTC ni lee nada dependiente del reloj; el número
  aleatorio del juego sale de contadores de frames, que son deterministas.
- El input se da por frame; el guion usa cantidades fijas de frames.

Los dos tests de determinismo lo comprueban en el mismo proceso, y la
comparación de capturas contra referencias generadas en otra corrida lo
comprueba entre procesos.

## El harness (`tests/emu/harness.py`)

Frontend libretro mínimo con `ctypes` (sin dependencias de pip):

```python
from harness import Emulator
emu = Emulator("mf_us.gba", "mf_us.map")      # un solo Emulator por proceso
emu.run(60)                                   # 60 frames
emu.run(30, "RIGHT+B"); emu.press("START")    # input por frame
emu.s16("gMainGameMode"); emu.u16("gSamusData+0x16")   # símbolos del .map
emu.read(0x06000000, 32)                      # cualquier región mapeada
emu.save_png("shot.png")                      # captura (PNG sin Pillow)
st = emu.save_state(); emu.load_state(st)
emu.cpu_registers()["pc"]; emu.symbolize(pc)  # PC desde el save state de mGBA
```

La memoria se lee a través del mapa de memoria que publica el core
(`RETRO_ENVIRONMENT_SET_MEMORY_MAPS`): EWRAM, IWRAM, I/O, paletas, VRAM, OAM y
ROM. Los símbolos se resuelven solo desde el `.map`. Los registros de la CPU
no son parte de la API libretro; `cpu_registers()` los saca del formato de
*save state* de mGBA y sirve para depurar.

### Depurar un cuelgue

1. Con el harness, ubicar el frame (modos, `cpu_registers()`, `symbolize`).
2. Guardar un estado justo antes (`open("x.ss","wb").write(emu.save_state()[:-8])`;
   los últimos 8 bytes son el contador de frames del harness).
3. Abrirlo en el depurador de línea de comandos de mGBA (`apt install
   mgba-sdl`):
   `SDL_VIDEODRIVER=dummy /usr/games/mgba -d -t x.ss mf_us.gba`, con
   `b <dir>`, `watch/w <dir>`, `trace <n>`, `c`.

## Qué hizo falta para que la ROM abierta arranque

Nada en `src/` ni `asm/`: solo datos de relleno, en `apply_known_layouts` de
`tools/open_assets/make_open_baserom.py`.

1. **Vector de interrupciones** (`sInterruptHandlers`): 13 punteros a
   `Dma2IntrCode`, `CallbackCallVblank`, `CallbackCallHBlank`,
   `CallbackCallVCount` y `Callback_Empty`. En cero, la primera IRQ de DMA2
   saltaba a 0 y la consola se reiniciaba en bucle durante el arranque.
2. **Datos de OAM de cinemáticas, final y selección de archivo**: en cero,
   los punteros a animaciones (`struct FrameData`) llevaban a leer un número
   de partes enorme y a escribir más allá del buffer de OAM, pisando
   `gVBlankCallback`. Se llenan con una palabra repetida que es la dirección
   (en el build) de una copia de sí misma alineada a 64 KiB: leída como
   `FrameData` es un terminador que apunta a un frame vacío, como frame tiene
   0 partes y como tabla de punteros vuelve a apuntar a algo válido. Las
   regiones que el código pasa a `LZ77UncompVram/Wram` quedan con cabecera 0
   (descomprimen a nada).
3. **Tablas de selección de archivo**: punteros por idioma a gráficos (→ LZ77
   vacío) y a tablas de texto (→ textos vacíos).
4. **Texto**: todo terminadores; las tablas `s*TextPointers*` apuntan a un
   texto vacío. Cada monólogo de la intro de partida nueva
   (`sMonologueText<Idioma>_<N>`) es "flecha, flecha, un carácter, flecha,
   fin", para que tanto las escenas que esperan "sigue texto" como las que
   esperan "fin" avancen con A.
5. **Voicegroups** (`sVoicegroup_*`): todas las voces tocan la primera
   muestra.

### Cómo se ubican esos datos

Para que cambios de la decomp o del layout no lo rompan en silencio:

- Las regiones se reconocen por el **símbolo** con que el código las incluye
  (`INCBIN`/`.incbin`, ver `tools/open_assets/layout.py`), no por el nombre de
  archivo en `database.json`. Si una regla no encuentra ninguna región, el
  generador falla con un error.
- Las fuentes LZ77 se detectan buscando en `src/` y `asm/` qué símbolos se
  pasan a `LZ77UncompVram/Wram` (en C y en asm).
- Lo que solo se conoce por su ubicación original (los rangos de datos de
  OAM, tres tablas de selección de archivo, el rango del texto) está dado como
  offset en la **base ROM**, que tiene el layout de la ROM original y no
  cambia aunque el build se desplace o `database.json` se divida en más
  piezas.
- Los **valores** que apuntan al build (funciones, otros datos) salen del ELF
  de la pasada anterior, así que siguen al código y los datos cuando se
  mueven. La corrida con la ROM desplazada lo comprueba.

## Limitaciones conocidas

- Samus no se dibuja todavía en la sala (la posición en RAM sí cambia y es lo
  que verifican los tests); la pantalla de selección de archivo se ve negra
  (sus gráficos descomprimen a nada). El arte es relleno.
- Las capturas dependen de la versión de mGBA; CI fija `ubuntu-24.04`
  (libretro-mgba 0.10.2). Con otra versión puede hacer falta regenerar
  referencias.
- Cuando una de estas regiones se decompile (se convierta en C/asm con
  símbolos), deja de venir de la base ROM y su regla deja de aplicarse; si era
  la única región de una regla, el generador avisa con un error y hay que
  quitar o ajustar la regla.
- El guion pulsa A cada 30 frames durante la intro; si cambia la duración de
  alguna escena, puede requerir más pulsos (`BOOT_SCRIPT` en `scenario.py`).
