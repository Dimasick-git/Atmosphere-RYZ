
# Ryazhenka 8.1.0

Ryazhenka 8.1.0 is based on Atmosphère 1.12.0, with upstream updates through
`c8b7316581a8081e5b9f7d767c27db5c0a4db906`, including support for Horizon OS 23.0.0.
The custom splash screen and `HOS|RYZ v8.1.0|E` / `HOS|RYZ v8.1.0|S`
version display are preserved. The internal Atmosphère version stays at 1.12.0.

The Ryazhenka display version is defined in
`libraries/libvapours/include/vapours/ams/ams_api_version.h`.
Build instructions are in [docs/building.md](docs/building.md).
Release changes and installation instructions (Russian) are in
[the Ryazhenka 8.1.0 release notes](docs/ryazhenka-8.1.0-release.md).

Legacy libnx homebrew (including older Chiaki and PPSSPP builds) keeps its TLS
slots at `0x108`, following the compatibility approach in Atmosphere-CNX.
The scheduler omits the TLS CPU-time write, exactly as CNX does, including before
libnx initializes its thread marker. A separate libnx check protects HOS 23.0.0's
new child-thread handle at `0x110`. SDK child-thread handle updates remain in place.
See [the compatibility notes](docs/ryazhenka-homebrew-compatibility.md) for details
and the on-console verification procedure.

![Banner](img/banner.png?raw=true)
=====

![License](https://img.shields.io/badge/License-GPLv2-blue.svg)
[![Chat on Discord](https://img.shields.io/badge/Discord-5865f2?logo=discord&logoColor=white)](https://discordapp.com/invite/ZdqEhed)
![Made with Notepad++](img/np++.png?raw=true)

Atmosphère is a work-in-progress customized firmware for the Nintendo Switch.

Components
=====

Atmosphère consists of multiple components, each of which replaces/modifies a different component of the system:

* Fusée: First-stage Loader, responsible for loading and validating stage 2 (custom TrustZone) plus package2 (Kernel/FIRM sysmodules), and patching them as needed. This replaces all functionality normally in Package1loader/NX Bootloader.
* Exosphère: Customized TrustZone, to run a customized Secure Monitor
* Thermosphère: EL2 EmuNAND support, i.e. backing up and using virtualized/redirected NAND images
* Stratosphère: Custom Sysmodule(s), both Rosalina style to extend the kernel/provide new features, and of the loader reimplementation style to hook important system actions
* Troposphère: Application-level Horizon OS patches, used to implement desirable CFW features

Licensing
=====

This software is licensed under the terms of the GPLv2, with exemptions for specific projects noted below.

You can find a copy of the license in the [LICENSE file](LICENSE).

Exemptions:
* [Nintendo](https://github.com/Nintendo) is exempt from GPLv2 licensing and may (at its option) instead license any source code authored for the Atmosphère project under the Zero-Clause BSD license.

Credits
=====

Atmosphère is currently being developed and maintained by __SciresM__, __TuxSH__, __hexkyz__, and __fincs__.<br>
In no particular order, we credit the following for their invaluable contributions:

* __switchbrew__ for the [libnx](https://github.com/switchbrew/libnx) project and the extensive [documentation, research and tool development](http://switchbrew.org) pertaining to the Nintendo Switch.
* __devkitPro__ for the [devkitA64](https://devkitpro.org/) toolchain and libnx support.
* __ReSwitched Team__ for additional [documentation, research and tool development](https://reswitched.github.io/) pertaining to the Nintendo Switch.
* __ChaN__ for the [FatFs](http://elm-chan.org/fsw/ff/00index_e.html) module.
* __Marcus Geelnard__ for the [bcl-1.2.0](https://sourceforge.net/projects/bcl/files/bcl/bcl-1.2.0) library.
* __naehrwert__ and __st4rk__ for the original [hekate](https://github.com/nwert/hekate) project and its hwinit code base.
* __CTCaer__ for the continued [hekate](https://github.com/CTCaer/hekate) project's fork and the [minerva_tc](https://github.com/CTCaer/minerva_tc) project.
* __m4xw__ for development of the [emuMMC](https://github.com/m4xw/emummc) project.
* __Riley__ for suggesting "Atmosphere" as a Horizon OS reimplementation+customization project name.
* __hedgeberg__ for research and hardware testing.
* __lioncash__ for code cleanup and general improvements.
* __jaames__ for designing and providing Atmosphère's graphical resources.
* Everyone who submitted entries for Atmosphère's [splash design contest](https://github.com/Atmosphere-NX/Atmosphere-splashes).
* _All those who actively contribute to the Atmosphère repository._
