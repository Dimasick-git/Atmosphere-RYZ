<p align="center">
  <img src="img/ryazhenka_logo.png" alt="Ryazhenka" width="220">
</p>

<h1 align="center">Atmosphère-RYZ · Ryazhenka</h1>

<p align="center">
  <img src="https://img.shields.io/badge/License-GPLv2-blue.svg" alt="License">
  <img src="https://img.shields.io/badge/base-Atmosph%C3%A8re-7c3aed.svg" alt="Base">
  <img src="https://img.shields.io/badge/patched-AOTag%20%7C%20Ryazhenka-ff2d55.svg" alt="Patched">
</p>

---

## 🇬🇧 English (short)

**Atmosphère-RYZ** ("Ryazhenka") is a patched fork of
[Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) — a work‑in‑progress
custom firmware for the Nintendo Switch. It is based on
[Atmosphere‑CNX](https://github.com/CostelaCNX/Atmosphere-CNX) (which tracks
upstream Atmosphère), but with the CNX branding removed and the following
changes on top:

- **Ryazhenka boot splash** instead of the CNX/Atmosphère logo.
- The compiled boot logo restored to the **original Atmosphère** artwork.
- **AOTag** PMC access patch in `exosphere` (ported from
  [Horizon‑OC](https://github.com/Horizon-OC/Horizon-OC)) — lets the aotag
  thermal sensor read memory temperatures.
- A single editable [`version.txt`](version.txt) that drives the on‑console
  version string (`Ryazhenka vX.Y.Z`) and the release name.
- **Automatic build & release** on every push to `main`, and an **automatic
  upstream‑sync pull request** when the original Atmosphère changes.

> ⚠️ This is an unofficial patched build. Do not report issues with it to the
> upstream Atmosphère / CNX / Horizon‑OC teams.

Detailed component documentation (in English) lives in [`docs/`](docs/main.md).

---

## 🇷🇺 Русский (подробно)

**Atmosphère‑RYZ** (кодовое имя «Ryazhenka» / Ряженка) — это пропатченный форк
[Atmosphère](https://github.com/Atmosphere-NX/Atmosphere), кастомной прошивки
для Nintendo Switch. Он собран на базе
[Atmosphere‑CNX](https://github.com/CostelaCNX/Atmosphere-CNX) (который
синхронизирован с оригинальной Atmosphère), но из него **полностью убран
брендинг CNX** и добавлены изменения, описанные ниже.

### Что изменено относительно CNX/оригинала

| Изменение | Описание |
|-----------|----------|
| 🎨 Загрузочный логотип | Splash‑экран при загрузке заменён на логотип **Ryazhenka** (`img/splash.png` / `img/splash.bin`, встраивается в `fusee/package3`). |
| 🔁 Компилируемый лого | Встроенный в модуль `boot` логотип возвращён к **оригинальному** виду Atmosphère (`boot_splash_screen_notext.inc`); CNX‑вариант удалён. |
| 🌡️ Патч AOTag | В `exosphere` добавлена таблица доступа к PMC‑регистрам (порт из [Horizon‑OC](https://github.com/Horizon-OC/Horizon-OC)), необходимая для работы термодатчика **aotag**. Только PMC‑часть; разгон RAM (EMC) не включён. |
| 🏷️ Версия | Версия задаётся одним файлом [`version.txt`](version.txt). Она показывается на консоли как `Ryazhenka vX.Y.Z` и используется как имя релиза. |
| ⚙️ Автосборка | При каждом push в `main` GitHub Actions автоматически собирает прошивку и публикует релиз с пометкой о патчах. |
| 🔄 Авто‑PR из оригинала | По расписанию проверяются изменения в оригинальной Atmosphère и автоматически создаётся pull request, который ты можешь применить или отклонить. |

### Как поменять версию

1. Открой [`version.txt`](version.txt) и впиши новый номер (например `8.0.1`).
2. Закоммить и запушь в `main`.
3. GitHub Actions сам пересоберёт прошивку и выпустит релиз `Ryazhenka v8.0.1`.

Подробнее — в [`docs/main.md`](docs/main.md), [`docs/building.md`](docs/building.md)
и [`docs/faq.md`](docs/faq.md).

### Компоненты Atmosphère

* **Fusée** — загрузчик первой стадии.
* **Exosphère** — кастомный Secure Monitor (здесь и живёт патч AOTag).
* **Thermosphère** — поддержка EmuNAND на уровне EL2.
* **Stratosphère** — кастомные системные модули.
* **Troposphère** — патчи уровня приложений Horizon OS.

---

## Лицензия / Licensing

Распространяется под лицензией **GPLv2** (см. [LICENSE](LICENSE)), с теми же
исключениями, что и у оригинальной Atmosphère.

This software is licensed under the terms of the GPLv2, with the same exemptions
as upstream Atmosphère.

## Благодарности / Credits

Проект **Atmosphère** разрабатывают и поддерживают __SciresM__, __TuxSH__,
__hexkyz__ и __fincs__. Патч AOTag — проект
[Horizon‑OC](https://github.com/Horizon-OC/Horizon-OC). База форка —
[Atmosphere‑CNX](https://github.com/CostelaCNX/Atmosphere-CNX).
Atmosphère‑RYZ лишь применяет описанные выше изменения поверх их труда.
