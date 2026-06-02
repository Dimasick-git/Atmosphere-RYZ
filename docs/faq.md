# FAQ / Частые вопросы — Atmosphère-RYZ

## 🇬🇧 English (short)

Common questions about the Ryazhenka fork: how versioning works, how the
auto-build/release works, what the AOTag patch does, and where the splash comes
from. Full answers in Russian below.

## 🇷🇺 Русский (подробно)

### Что такое Atmosphère‑RYZ?

Пропатченный форк Atmosphère на базе Atmosphere‑CNX, с убранным брендингом CNX,
логотипом Ryazhenka, патчем AOTag из Horizon‑OC и автосборкой. Это
**неофициальная** сборка — не пиши о её проблемах командам Atmosphère/CNX/Horizon‑OC.

### Как поменять версию прошивки?

Открой [`version.txt`](../version.txt) в корне репозитория, впиши новый номер
(например `8.0.1`, без `v`), закоммить и запушь в `main`. Скрипт
`scripts/apply_version.sh` подставит `Ryazhenka v8.0.1` в строку версии,
показываемую на консоли, а CI выпустит релиз с тем же именем.

### Как работает автосборка и релизы?

При каждом push в `main` workflow `.github/workflows/build-release.yml`:
1. собирает прошивку в Docker‑образе `devkitpro/devkita64`;
2. применяет версию из `version.txt`;
3. встраивает splash Ryazhenka в `package3`;
4. публикует релиз `Ryazhenka vX.Y.Z` с архивом и пометкой, что это патченная версия.

### Что делает патч AOTag?

`exosphere` (Secure Monitor) обычно блокирует запись в часть PMC‑регистров.
Термодатчик **aotag** (порт драйвера из L4T, используется в Horizon‑OC для оценки
температуры памяти) требует доступа к этим регистрам. Патч добавляет таблицу
доступа `RtcPmcAccessTable`, разрешающую нужный PMC‑доступ. Включена **только**
PMC‑часть; разгон оперативной памяти (EMC) сюда не входит.

> ⚠️ Сам по себе патч лишь *разрешает* доступ. Чтобы читать температуру aotag,
> нужен соответствующий overclock‑сисмодуль (например, из Horizon‑OC),
> устанавливаемый отдельно на SD‑карту.

### Откуда взялся логотип загрузки?

Splash‑экран (`img/splash.png` / `img/splash.bin`, 1280×720) заменён на логотип
**Ryazhenka** и встраивается в `fusee/package3`. Встроенный в модуль `boot`
логотип (`.inc`) возвращён к **оригинальному** виду Atmosphère.

### Что значит «June 15th» в релизах оригинала?

Это давняя шутка SciresM из оригинальной Atmosphère: «June 15» — пропущенная
дата первого релиза 2018 года, которую с тех пор шутливо упоминают в каждом
релизе. К Ryazhenka отношения не имеет, но сохранена как часть наследия проекта.

### Как обновляться вслед за оригинальной Atmosphère?

Workflow `.github/workflows/upstream-sync.yml` периодически проверяет оригинальный
репозиторий и при новых коммитах автоматически создаёт pull request. Ты сам
решаешь, применять его или нет.
