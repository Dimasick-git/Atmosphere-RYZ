# fusée

## English (summary)

fusée is Atmosphère's custom first-stage bootloader. It is the first code that runs
on the hardware, delivered as a standalone RCM payload (via CVE-2018-6242). It
performs low-level hardware init, sets up the cryptosystem, mounts/emulates the
eMMC, injects and patches system modules, and launches exosphère.

## Русский (подробно)

fusée — кастомный загрузчик первой стадии Atmosphère; первый код, исполняемый на
оборудовании. Поставляется как отдельный payload, запускаемый через RCM
(эксплуатация уязвимости CVE-2018-6242).

Отвечает за:

- низкоуровневую инициализацию оборудования Nintendo Switch;
- настройку криптосистемы;
- монтирование/эмуляцию eMMC;
- инъекцию и патчинг системных модулей;
- запуск компонента exosphère.

Замечание Ryazhenka: логотип загрузки (`img/splash.bin`) встраивается в `package3`
скриптом `fusee/build_package3.py` при сборке и заменён на логотип Ryazhenka.
