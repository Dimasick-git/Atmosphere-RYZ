# exosphère

## English (summary)

exosphère is a reimplementation of the Horizon OS Secure Monitor (TrustZone). It
runs at EL3, handling sensitive cryptographic operations and per-CPU power
management. It adds custom SMCs and configuration items for the homebrew
ecosystem. Ryazhenka note: the AOTag patch lives here — it adds an `RtcPmc`
register access table so the secure monitor permits the PMC access required by the
aotag thermal sensor (PMC only, no RAM/EMC overclock).

## Русский (подробно)

exosphère — кастомная реимплементация Secure Monitor (он же TrustZone) ОС Horizon.
Работает в режиме наивысшей привилегии (EL3) основного процессора и отвечает за
чувствительные криптографические операции и управление питанием каждого CPU.

Замечание Ryazhenka: патч AOTag находится в этом компоненте. Он добавляет таблицу
доступа `RtcPmcAccessTable` (порт из Horizon-OC), разрешающую запись в PMC-регистры,
необходимую термодатчику aotag. Включена только PMC-часть; разгон RAM (EMC) не
добавляется. См. `exosphere/program/source/smc/secmon_smc_register_access.cpp`.

## Расширения / Extensions

exosphère добавляет к оригинальному Secure Monitor собственные SMC (Secure Monitor
Calls), необходимые экосистеме homebrew:

```
uint32_t smc_ams_iram_copy(smc_args_t *args);
uint32_t smc_ams_write_address(smc_args_t *args);
uint32_t smc_ams_get_emummc_config(smc_args_t *args);
```

Также расширяется функциональность двух стандартных SMC получения/установки
элементов конфигурации. Собственные элементы конфигурации exosphère:

```
CONFIGITEM_EXOSPHERE_VERSION = 65000,
CONFIGITEM_NEEDS_REBOOT = 65001,
CONFIGITEM_NEEDS_SHUTDOWN = 65002,
CONFIGITEM_EXOSPHERE_VERHASH = 65003,
CONFIGITEM_HAS_RCM_BUG_PATCH = 65004,
CONFIGITEM_SHOULD_BLANK_PRODINFO = 65005,
CONFIGITEM_ALLOW_CAL_WRITES = 65006,
```

### smc_ams_iram_copy

Копирование до одной страницы между DRAM и IRAM. Аргументы:

```
args->X[1] = адрес в DRAM (транслируется ядром), выравнивание по 4 байтам.
args->X[2] = адрес в IRAM, выравнивание по 4 байтам.
args->X[3] = размер (<= 0x1000, выравнивание по 4 байтам).
args->X[4] = 0 — чтение, 1 — запись.
```

### smc_ams_write_address

Запись в страницу DRAM. Аргументы:

```
args->X[1] = виртуальный адрес, выравнивание по размеру, читаемый из EL0.
args->X[2] = значение.
args->X[3] = размер (1, 2, 4 или 8).
```

### smc_ams_get_emummc_config

Получение конфигурации текущего контекста [emummc](emummc.md). Аргументы:

```
args->X[1] = MMC id, выравнивание по размеру, читаемый из EL0.
args->X[2] = указатель на вывод (пути для file-based + nintendo dir), не менее 0x100 байт.
```

### Элементы конфигурации

- `CONFIGITEM_EXOSPHERE_VERSION` — версия exosphère.
- `CONFIGITEM_NEEDS_REBOOT` — перезагрузка в RCM или warmboot-payload.
- `CONFIGITEM_NEEDS_SHUTDOWN` — выключение через warmboot-payload.
- `CONFIGITEM_EXOSPHERE_VERHASH` — git-хэш текущей сборки exosphère.
- `CONFIGITEM_HAS_RCM_BUG_PATCH` — пропатчена ли уязвимость CVE-2018-6242.
- `CONFIGITEM_SHOULD_BLANK_PRODINFO` — симулировать ли «пустой» PRODINFO
  (см. [configurations.md](../features/configurations.md)).
- `CONFIGITEM_ALLOW_CAL_WRITES` — разрешать ли запись в раздел калибровки.

## Встроенные payload'ы

- `lp0fw` — пробуждение системы при warm boot.
- `sc7fw` — перевод системы в сон при warm boot.
- `rebootstub` — перезагрузка системы в произвольный payload.
