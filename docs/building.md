# Building Atmosphère-RYZ / Сборка Atmosphère-RYZ

## 🇬🇧 English (short)

Building relies almost entirely on the [devkitPro](https://devkitpro.org)
toolchain. You normally do **not** need to build locally — every push to `main`
is built automatically by GitHub Actions (see `.github/workflows/build-release.yml`).
To build by hand, install devkitA64/devkitARM, run `scripts/apply_version.sh`,
then `make`, then inject the splash with `utilities/insert_splash_screen.py`.

## 🇷🇺 Русский (подробно)

Сборка почти полностью опирается на тулчейн [devkitPro](https://devkitpro.org).

> 💡 В большинстве случаев собирать вручную **не нужно**: при каждом push в `main`
> GitHub Actions сам собирает прошивку и публикует релиз. Ручная сборка нужна
> только для локальной разработки.

### Зависимости

+ [devkitA64](https://devkitpro.org)
+ [devkitARM](https://devkitpro.org)
+ [Python 3](https://www.python.org)
+ [LZ4](https://pypi.org/project/lz4)
+ [Pillow](https://pypi.org/project/Pillow) (для генерации splash, опционально)
+ [PyCryptodome](https://pypi.org/project/pycryptodome) (опционально)
+ [hactool](https://github.com/SciresM/hactool)

### Инструкция (ручная сборка)

1. Установи и настрой devkitPro по [официальному гайду](https://devkitpro.org/wiki/Getting_Started).
2. Через `(dkp-)pacman` поставь пакеты:
   + `switch-dev`
   + `switch-glm`
   + `switch-libjpeg-turbo`
   + `devkitARM`
   + `devkitarm-rules`
   + `hactool`
3. Через `pip` поставь библиотеку, нужную для [exosphère](components/exosphere.md):
   + `lz4`
4. Применить версию из `version.txt`:
   ```sh
   scripts/apply_version.sh
   ```
5. Собрать всё из корня репозитория:
   ```sh
   make
   ```
6. Встроить логотип Ryazhenka в собранный `package3`:
   ```sh
   python utilities/insert_splash_screen.py img/splash.png fusee/package3
   ```

### Автосборка (рекомендуется)

Просто запушь изменения в `main`. Workflow `build-release` соберёт прошивку в
официальном Docker‑образе `devkitpro/devkita64`, применит версию из `version.txt`,
встроит splash и опубликует релиз `Ryazhenka vX.Y.Z` с артефактами. Подробнее —
в [faq.md](faq.md).
