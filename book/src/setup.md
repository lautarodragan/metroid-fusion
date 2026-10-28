# Setup y build

## Dependencias

- [agbcc](https://github.com/pret/agbcc)
- `binutils-arm-none-eabi`
- Un base ROM por cada ROM que quieras generar (por ejemplo
  `mf_us_baserom.gba` para generar `mf_us.gba`). Si no tenés el ROM original,
  igual podés verificar tus cambios con el
  [check sintético](docs/synthetic_check.md).
- `python3`
- `g++`

## Setup

- **Solo Windows:** instalá y configurá
  [WSL](https://docs.microsoft.com/en-us/windows/wsl/install).
- Corré `sudo apt update`, por las dudas.
- Instalá `binutils-arm-none-eabi`: `sudo apt-get install binutils-arm-none-eabi`
- Instalá `git`: `sudo apt-get install git`
- Instalá `make`: `sudo apt-get install make`

### agbcc

La forma más rápida es usar el script del repositorio:

```sh
tools/setup_toolchain.sh
```

Clona, compila e instala agbcc en un solo paso (en `/opt/agbcc`, con symlinks
en `/usr/local/bin`; mirá el script para ver las opciones).

Si preferís hacerlo a mano:

1. Cloná agbcc: `git clone https://github.com/pret/agbcc`
2. Entrá a la carpeta (`cd agbcc`) y compilalo (`./build.sh`).
3. Después, una de dos:
   - Instalá agbcc dentro de este proyecto con su script `./install.sh <path>`,
     donde `<path>` es la raíz de este repositorio, o
   - Agregá agbcc al `PATH` (`export PATH="<agbcc_path>:$PATH"`, donde
     `<agbcc_path>` es la ruta completa al directorio de agbcc).

## Build

- Corré `make clean` si hace falta.
  - `make clean DATA=1` borra también los datos extraídos.
- Corré el extractor de datos si hace falta: `python3 tools/extractor.py`
  - Con `-r` elegís una región distinta de `us` (por ejemplo `-r jp`).
  - Con `-d` se extraen solo los datos de debug del ROM beta de USA (necesario
    para generar un ROM con funciones de debug).
- Corré `make` (se recomienda `-j` para acelerar).
- Para generar otra versión del ROM, cualquiera de estas dos:
  - Indicala directamente (por ejemplo `make us_debug` para el ROM de USA con
    funciones de debug).
  - Usá las variables `REGION` (nombre de la región, por defecto `us`) y
    `DEBUG` (`0` o `1`, por defecto `0`).
- Para simplificar, podés combinar los comandos:
  `python3 tools/extractor.py && make -j`

## Verificar que el ROM coincide

- `make check` compara el ROM generado con el original.
- `./check_roms.sh` genera y verifica los ROMs de todas las regiones
  soportadas (necesitás un base ROM por región).
- `make check-synthetic` verifica sin el ROM original; ver
  [Verificación sin ROM](docs/synthetic_check.md).
