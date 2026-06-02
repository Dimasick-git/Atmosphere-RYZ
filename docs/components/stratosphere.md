# stratosphère

## English (summary)

stratosphère customizes Horizon OS at the system level: it reimplements several
system modules and adds custom ones that extend system functionality. The module
list is below.

## Русский (подробно)

stratosphère кастомизирует Horizon OS на системном уровне: реимплементирует ряд
системных модулей и добавляет собственные, расширяющие функциональность системы.

### Модули

- [ams_mitm](modules/ams_mitm.md)
- [boot](modules/boot.md)
- [boot2](modules/boot2.md)
- [creport](modules/creport.md)
- [dmnt](modules/dmnt.md)
- [eclct.stub](modules/eclct.stub.md)
- [erpt](modules/erpt.md)
- [fatal](modules/fatal.md)
- [jpegdec](modules/jpegdec.md)
- [loader](modules/loader.md)
- [ncm](modules/ncm.md)
- [pgl](modules/pgl.md)
- [pm](modules/pm.md)
- [ro](modules/ro.md)
- [sm](modules/sm.md)
- [spl](modules/spl.md)

Замечание Ryazhenka: строка версии, отображаемая на консоли, формируется модулем
`ams_mitm` (`set_mitm`) и здесь равна `Ryazhenka vX.Y.Z` (см. `version.txt`).
