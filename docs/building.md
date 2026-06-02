# Building Atmosphère-RYZ

## English (summary)

The build uses the devkitPro toolchain (devkitA64 + devkitARM). Local builds are
optional: every push to `main` is built by GitHub Actions
(`.github/workflows/build-release.yml`) in the `devkitpro/devkita64` container.
Manual build: install the toolchain and `lz4`/`Pillow`, run
`scripts/apply_version.sh`, run `make`, then inject the splash with
`utilities/insert_splash_screen.py`.

## Русский (подробно)

Сборка опирается на тулчейн [devkitPro](https://devkitpro.org). Локальная сборка
не обязательна: при каждом push в `main` прошивка собирается в GitHub Actions
(контейнер `devkitpro/devkita64`) и публикуется релиз.

### Зависимости

- devkitA64, devkitARM (devkitPro);
- Python 3;
- `lz4` (требуется сборкой);
- `Pillow` (требуется `utilities/insert_splash_screen.py`);
- `hactool`.

### Ручная сборка

1. Установить и настроить devkitPro: https://devkitpro.org/wiki/Getting_Started
2. Установить пакеты через `(dkp-)pacman`:
   `switch-dev`, `switch-glm`, `switch-libjpeg-turbo`, `devkitARM`,
   `devkitarm-rules`, `hactool`.
3. Установить Python-модули: `pip install lz4 Pillow`.
4. Применить версию из `version.txt`:
   ```sh
   scripts/apply_version.sh
   ```
5. Собрать из корня репозитория:
   ```sh
   make
   ```
6. Встроить splash Ryazhenka в `package3`:
   ```sh
   python utilities/insert_splash_screen.py img/splash.png fusee/package3
   ```

### Автоматическая сборка

Push в `main` запускает workflow `build-release`: применяется версия из
`version.txt`, выполняется `make`, встраивается splash, артефакты упаковываются и
публикуется релиз `Ryazhenka vX.Y.Z`. Подробности — в [faq.md](faq.md).
