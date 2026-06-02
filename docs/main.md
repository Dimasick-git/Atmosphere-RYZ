# Atmosphère-RYZ (Ryazhenka)

## 🇬🇧 English (short)

Atmosphère-RYZ is a patched fork of Atmosphère, a custom firmware for the
Nintendo Switch. It keeps Atmosphère's multi-layered design and adds the
Ryazhenka boot splash, the Horizon-OC **AOTag** PMC patch, an editable
`version.txt`, and automated build/release. The detailed per-component docs
linked below remain in English (upstream reference).

## 🇷🇺 Русский (подробно)

Atmosphère‑RYZ («Ryazhenka») — кастомная прошивка для Nintendo Switch,
основанная на [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere). Как и
оригинал, она построена по многослойному принципу: каждый слой заменяет или
дополняет отдельный компонент системы Switch.

### Компоненты

Atmosphère состоит из шести основных компонентов (названных по слоям атмосферы):
+ [fusée](components/fusee.md) — загрузчик первой стадии;
+ [exosphère](components/exosphere.md) — кастомный Secure Monitor (**здесь патч AOTag**);
+ [thermosphère](components/thermosphere.md) — гипервизор / EmuNAND на EL2;
+ [mesosphère](components/mesosphere.md) — реимплементация ядра Horizon;
+ [stratosphère](components/stratosphere.md) — кастомные системные модули;
+ [troposphère](components/troposphere.md) — патчи уровня приложений.

Дополнительные компоненты:
+ [emummc](components/emummc.md)
+ [libraries](components/libraries.md)

### Возможности

+ [Читы / Cheats](features/cheats.md)
+ [Конфигурации / Configurations](features/configurations.md)
+ [DNS MITM](features/dns_mitm.md)

### Отличия Ryazhenka от оригинала

+ **Логотип загрузки** заменён на Ryazhenka (`img/splash.png` → `fusee/package3`).
+ **Компилируемый лого** модуля `boot` возвращён к оригиналу Atmosphère.
+ **AOTag**: патч доступа к PMC в `exosphere` (порт из Horizon‑OC) для термодатчика aotag.
+ **Версия** задаётся файлом [`version.txt`](../version.txt) (`Ryazhenka vX.Y.Z`).
+ **Автосборка и авто‑релиз** через GitHub Actions, **авто‑PR** при обновлениях оригинала.

### Сборка

Руководство по сборке — в [building.md](building.md).

### История изменений

Список изменений — в [changelog.md](changelog.md).

### Планы

Планируемые возможности оригинальной Atmosphère — в [roadmap.md](roadmap.md).
