# DNS.mitm

## English (summary)

DNS.mitm redirects DNS resolution requests. By default it redirects Nintendo
telemetry servers to a loopback address. It is configured via an extended `hosts`
file format parsed once at startup. Hosts file selection order, atmosphère
defaults, debug logging, and a full opt-out are described below.

## Русский (подробно)

DNS.mitm (доступен начиная с 0.18.0) перенаправляет запросы разрешения DNS. По
умолчанию перенаправляет запросы к официальным серверам телеметрии Nintendo на
loopback-адрес.

### Файлы hosts

DNS.mitm настраивается через слегка расширенный формат файла `hosts`, который
разбирается один раз при запуске системы. Расширения формата:

- `*` — символ подстановки, соответствует 0 или более любым символам в имени хоста;
- `%` — подстановка значения `nsd!environment_identifier` (на розничных устройствах
  всегда `lp1`).

Если домену соответствуют несколько записей, используется последняя по порядку.

Homebrew может инициировать повторный разбор файла hosts, отправив расширенную
IPC-команду 65000 («AtmosphereReloadHostsFile») в сессию `sfdnsres`.

### Выбор файла hosts

Atmosphère читает hosts из следующих путей по порядку, останавливаясь на первом
успешно прочитанном:

- (только emummc) `/atmosphere/hosts/emummc_%04lx.txt` (с id из `emummc.ini`);
- (только emummc) `/atmosphere/hosts/emummc.txt`;
- (только sysmmc) `/atmosphere/hosts/sysmmc.txt`;
- `/atmosphere/hosts/default.txt`.

Если `default.txt` отсутствует, Atmosphère создаёт его со значениями по умолчанию.

### Значения по умолчанию

По умолчанию перенаправления Atmosphère применяются дополнительно к содержимому
загруженного файла hosts (как если бы они были добавлены в начало файла). Это
снижает риск утечки телеметрии, если пользователь забыл обновить свой hosts при
обновлении системы. Отключается через `atmosphere!add_defaults_to_dns_hosts = u8!0x0`
в `system_settings.ini`.

Текущие перенаправления по умолчанию:

```
# Серверы телеметрии Nintendo
127.0.0.1 receive-%.dg.srv.nintendo.net receive-%.er.srv.nintendo.net
```

### Отладка

При запуске (или повторном разборе) DNS.mitm пишет в
`/atmosphere/logs/dns_mitm_startup.log` выбранный файл hosts и все перенаправления.
При `atmosphere!enable_dns_mitm_debug_log = u8!0x1` в `system_settings.ini` все
запросы GetHostByName/GetAddrInfo логируются в `/atmosphere/logs/dns_mitm_debug.log`.

### Полное отключение

Установить `atmosphere!enable_dns_mitm = u8!0x0` в `system_settings.ini`.
