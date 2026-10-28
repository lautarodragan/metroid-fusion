# Contribuir

<!-- Basado en CONTRIBUTING.md de la raíz del repositorio. Si cambian las
     reglas allí, actualizar también esta página. -->

> La versión de referencia es
> [CONTRIBUTING.md](https://github.com/lautarodragan/metroid-fusion/blob/main/CONTRIBUTING.md)
> en el repositorio (en inglés). Si esta traducción y ese archivo difieren,
> vale el original.

## Importante: clean room

Cualquiera que quiera contribuir **DEBE** leer lo siguiente y seguir los pasos
indicados, para no violar ningún copyright.

Esta decompilación es un
[diseño de sala limpia (*clean room design*)](https://en.wikipedia.org/wiki/Clean_room_design).
**NO DEBE** incorporar ningún código que pertenezca a Nintendo ni a otros
terceros.

Para lograrlo, todo el código tiene que escribirse completamente desde cero,
sin consultar ningún código de terceros, **haya sido filtrado o no**.

De esto se deriva el siguiente requisito para quienes contribuyen:

- Quienes contribuyen **NO DEBEN** estudiar ni consultar ningún código que
  pertenezca a Nintendo o a otros terceros.

## Enviar un cambio

1. Cloná este repositorio y seguí las instrucciones de [setup](setup.md), si
   todavía no lo hiciste.
2. Para cada conjunto de cambios que quieras enviar, creá una rama a partir de
   `main` (asegurate de estar en el último commit).
3. Cuando estés por enviar los cambios, verificá que el ROM siga compilando
   (`make`).
4. Si compila, verificá que el ROM siga coincidiendo con el base ROM
   (`make check`).
   - Recomendado: corré `./check_roms.sh` para generar y verificar los ROMs de
     todas las regiones soportadas (puede requerir `chmod +x check_roms.sh`).
     Necesitás un base ROM por cada región soportada.
   - Sin base ROM, usá `make check-synthetic`
     ([Verificación sin ROM](docs/synthetic_check.md)).
5. Abrí un PR en GitHub con una descripción que resuma tus cambios.
