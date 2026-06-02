# Configurations

## English (summary)

Atmosphère is configured through several ini files on the SD card: `stratosphere.ini`
(nogc and other sysmodule options), `exosphere.ini` (debug modes, PRODINFO blanking),
`override_config.ini` (button override keys), `system_settings.ini` (firmware debug
settings), and `emummc.ini`. A custom 1280x720 boot splash can be injected with
`utilities/insert_splash_screen.py`. Full reference in Russian below.

## Русский (подробно)

Atmosphère настраивается через несколько ini-файлов на SD-карте. Шаблоны по
умолчанию находятся в `/atmosphere/config_templates/`.

### stratosphere.ini

Файл конфигурации user-space системных модулей, используемый fusée. Путь:
`/atmosphere/config/`.

#### Защита «nogc»

«nogc» отключает считыватель игровых картриджей, чтобы предотвратить обновление его
прошивки после обновления системы с младшей версии без прожига предохранителей
(актуально для 4.0.0 и 9.0.0). По умолчанию Atmosphère включает защиту автоматически.

```
[stratosphere]
nogc = X
```
```
1 = принудительно включить nogc (считыватель всегда отключён).
0 = принудительно выключить nogc (считыватель всегда включён).
```

### Загрузочный splash

Atmosphère отображает собственный splash при загрузке; его можно заменить.
Разрешение — 1280x720. Встраивание выполняется скриптом
`/utilities/insert_splash_screen.py`:

`python insert_splash_screen.py <путь к изображению> <путь к /atmosphere/package3 на SD>`

Замечание Ryazhenka: в этой сборке splash по умолчанию заменён на логотип Ryazhenka
(`img/splash.png` / `img/splash.bin`), и его встраивание выполняется при сборке.

### emummc.ini

Файл конфигурации компонента [emummc](../components/emummc.md). Путь: `/emuMMC/`.
Документация — в репозитории проекта: https://github.com/m4xw/emuMMC

### exosphere.ini

Файл конфигурации exosphère. Путь: корень SD-карты.

#### Режимы отладки

По умолчанию Atmosphère сообщает ядру Horizon, что отладка включена, но usermode-отладка
выключена. Изменение поведения:

```
[exosphere]
debugmode = X
debugmode_user = X
```
```
1 = включить
0 = выключить
```

#### Обнуление PRODINFO

Atmosphère позволяет «обнулить» заводские калибровочные данные (PRODINFO) в эмулируемой
или системной eMMC. Подробности — в файле-шаблоне. Использование не рекомендуется.

### override_config.ini

Путь: `/atmosphere/config/`. Разбирается при загрузке. Позволяет привязать кнопки к
действиям (например, запуск Homebrew Menu или включение менеджера читов).

Допустимые кнопки для записей `override_key`:

| Кнопка | Имя в .ini |
| ------ | ---------- |
| A | A |
| B | B |
| X | X |
| Y | Y |
| Левый стик | LS |
| Правый стик | RS |
| L | L |
| R | R |
| ZL | ZL |
| ZR | ZR |
| + | PLUS |
| - | MINUS |
| Влево (крестовина) | DLEFT |
| Вверх (крестовина) | DUP |
| Вправо (крестовина) | DRIGHT |
| Вниз (крестовина) | DDOWN |
| SL | SL |
| SR | SR |

Восклицательный знак перед кнопкой инвертирует поведение: игра запускается при
удержании этой кнопки, иначе — Homebrew Menu. Например, `override_key=!R` запустит
игру только при удержании R, иначе откроется Homebrew Menu.

### system_settings.ini

Путь: `/atmosphere/config/`. Позволяет переопределять отладочные настройки прошивки.

Идентификатор настройки имеет вид `name!key` и представляется секцией `name` с записью
`key`:

```
[name]
key = ...
```

Значения хранятся как пара `type_identifier!value_store`. Некорректная строка значения
вызывает fatal error при загрузке. Пример (`eupld!upload_enabled = 0`):

```
[eupld]
upload_enabled = u8!0x0
```

#### Поддерживаемые типы

- Строки — идентификаторы `str`, `string`; строка используется напрямую (с нулевым
  терминатором).
- Целочисленные — `u8`, `u16`, `u32`, `u64`; парсятся через `strtoul(value, NULL, 0)`;
  разрядность определяется идентификатором.
- Сырые байты — `hex`, `bytes`; шестнадцатеричная строка чётной длины (иначе fatal error).

### Флаги, специфичные для контента

Поведение CFW можно настраивать по наличию `flags` на SD-карте. На уровне программы
помещением `<flag_name>.flag` в `/atmosphere/contents/<program_id>/flags/`:

- `boot2` — программа должна запускаться в процессе `boot2`;
- `redirect_save` — сохранения программы перенаправляются на SD-карту.
