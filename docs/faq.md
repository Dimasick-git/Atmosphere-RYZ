# FAQ — Atmosphère-RYZ

## English (summary)

Covers: what this fork is, how versioning works, how the automatic build/release
works, what the AOTag patch does, the boot splash, and upstream synchronization.
Details in Russian below.

## Русский (подробно)

### Что такое Atmosphère-RYZ

Пропатченный форк Atmosphère на базе Atmosphere-CNX: брендинг CNX удалён, добавлены
логотип Ryazhenka, патч AOTag (из Horizon-OC), версионирование через `version.txt`
и CI. Неофициальная сборка — проблемы с ней не следует сообщать командам
Atmosphère / CNX / Horizon-OC.

### Как изменить версию прошивки

Указать номер в `version.txt` (например, `8.0.1`, без `v`), закоммитить и запушить
в `main`. Скрипт `scripts/apply_version.sh` подставит `Ryazhenka v8.0.1` в строку
версии на консоли; CI выпустит релиз с тем же именем.

### Как работает автосборка и релизы

Workflow `.github/workflows/build-release.yml` при push в `main`:

1. собирает прошивку в контейнере `devkitpro/devkita64`;
2. применяет версию из `version.txt`;
3. встраивает splash Ryazhenka в `package3`;
4. публикует релиз `Ryazhenka vX.Y.Z` с архивом артефактов и пометкой о патчах.

### Что делает патч AOTag

Secure Monitor (`exosphere`) по умолчанию блокирует запись в часть PMC-регистров.
Термодатчик aotag (драйвер, портированный из L4T; в Horizon-OC используется для
оценки температуры памяти) требует доступа к этим регистрам. Патч добавляет
таблицу доступа `RtcPmcAccessTable`, разрешающую необходимый PMC-доступ. Включена
только PMC-часть; разгон оперативной памяти (EMC) не входит в патч.

Патч лишь разрешает доступ. Для чтения температуры aotag требуется
соответствующий overclock-сисмодуль (например, из Horizon-OC), устанавливаемый
отдельно на SD-карту.

### Загрузочный логотип

Splash (`img/splash.png`, `img/splash.bin`, 1280×720) заменён на логотип Ryazhenka
и встраивается в `fusee/package3`. Встроенный в модуль `boot` логотип (`.inc`)
возвращён к оригиналу Atmosphère.

### Синхронизация с оригинальной Atmosphère

Workflow `.github/workflows/upstream-sync.yml` периодически (cron) проверяет
upstream-репозиторий. При новых коммитах их изменения накладываются на отдельную
ветку и открывается pull request для ручного просмотра и применения.
Автоматический мерж не выполняется.

### Назначение «June 15th» в релизах оригинала

Исторический мем оригинальной Atmosphère (пропущенная дата релиза 2018 года).
К Ryazhenka не относится; упоминается только как часть наследия проекта.
