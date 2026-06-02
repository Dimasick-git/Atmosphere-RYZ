# Atmosphère-RYZ

## English (summary)

Atmosphère-RYZ is a patched fork of Atmosphère for the Nintendo Switch, based on
Atmosphere-CNX. It preserves Atmosphère's layered architecture and adds: the
Ryazhenka boot splash, the Horizon-OC AOTag PMC patch in `exosphere`, a single
`version.txt` version source, and CI for automatic build/release and upstream
synchronization. Component reference docs are linked below.

## Русский (подробно)

Atmosphère-RYZ — пропатченный форк Atmosphère для Nintendo Switch на базе
Atmosphere-CNX. Сохраняет многослойную архитектуру Atmosphère: каждый слой
заменяет или дополняет отдельный компонент системы.

### Компоненты

Основные компоненты:

- [fusée](components/fusee.md) — загрузчик первой стадии;
- [exosphère](components/exosphere.md) — Secure Monitor (EL3); содержит патч AOTag;
- [thermosphère](components/thermosphere.md) — гипервизор EL2;
- [mesosphère](components/mesosphere.md) — реимплементация ядра Horizon (EL1);
- [stratosphère](components/stratosphere.md) — системные модули (EL0);
- [troposphère](components/troposphere.md) — патчи уровня приложений.

Вспомогательные компоненты:

- [emummc](components/emummc.md) — эмуляция eMMC;
- [libraries](components/libraries.md) — библиотеки разработки.

### Возможности

- [Читы](features/cheats.md)
- [Конфигурации](features/configurations.md)
- [DNS MITM](features/dns_mitm.md)

### Изменения Ryazhenka относительно базы

- Загрузочный splash заменён на Ryazhenka (`img/splash.png` -> `fusee/package3`).
- Компилируемый лого модуля `boot` возвращён к оригиналу Atmosphère.
- Патч AOTag: доступ к PMC в `exosphere` (порт из Horizon-OC) для термодатчика aotag.
- Версия задаётся файлом [`version.txt`](../version.txt) (`Ryazhenka vX.Y.Z`).
- Автосборка/авто-релиз и авто-PR синхронизации с upstream (GitHub Actions).

### Ссылки

- Сборка: [building.md](building.md)
- История изменений: [changelog.md](changelog.md)
- Планы (upstream): [roadmap.md](roadmap.md)
- Частые вопросы: [faq.md](faq.md)
