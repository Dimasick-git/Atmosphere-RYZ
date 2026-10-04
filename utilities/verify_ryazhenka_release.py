#!/usr/bin/env python3
"""Verify a locally built Ryazhenka release before copying it to an SD card."""
import hashlib
from pathlib import Path
import re
import struct
import sys
import zipfile


def verify(archive_path):
    root = Path(__file__).resolve().parent.parent
    header = (root / "libraries/libvapours/include/vapours/ams/ams_api_version.h").read_text()
    ryazhenka = re.search(r'^#define RYAZHENKA_RELEASE_VERSION_STRING "([0-9.]+)"$', header, re.M).group(1)

    def version(prefix):
        return tuple(int(re.search(r'^#define ' + prefix + '_' + part + r'\s+(\d+)$', header, re.M).group(1))
                     for part in ("MAJOR", "MINOR", "MICRO"))

    with zipfile.ZipFile(archive_path) as archive:
        bad_file = archive.testzip()
        if bad_file is not None:
            raise ValueError("Invalid ZIP entry: " + bad_file)
        package = archive.read("atmosphere/package3")
        payload = archive.read("atmosphere/reboot_payload.bin")
        if len(package) != 0x800000 or package[:4] != b"PK31" or package[0x20:0x24] != b"FSS0":
            raise ValueError("Invalid package3 header or size")
        if tuple(reversed(package[0x35:0x38])) != version("ATMOSPHERE_SUPPORTED_HOS_VERSION"):
            raise ValueError("Incorrect supported HOS version")
        if tuple(reversed(package[0x39:0x3C])) != version("ATMOSPHERE_RELEASE_VERSION"):
            raise ValueError("Incorrect internal Atmosphere version")

        entries = {}
        for index in range(struct.unpack_from("<I", package, 0x30)[0]):
            offset, size, kind, _, _, _, _, name = struct.unpack_from("<IIBBBBI16s", package, 0x40 + 0x20 * index)
            name = name.rstrip(b"\0").decode("ascii")
            if offset < 0x800 or offset + size > len(package):
                raise ValueError("Invalid component bounds: " + name)
            entries[name] = package[offset:offset + size]

        for index in range(8):
            meta = 0x400 + 0x30 * index
            offset, size = struct.unpack_from("<II", package, meta + 8)
            data = package[0x100000 + offset:0x100000 + offset + size]
            if data[:4] != b"KIP1" or hashlib.sha256(data).digest() != package[meta + 16:meta + 48]:
                raise ValueError("Invalid embedded KIP or hash: " + str(index))

        if entries["fusee"] != payload:
            raise ValueError("Fusee and reboot payload do not match")
        if package[0x400000:0x7C0000] != (root / "img/splash.bin").read_bytes():
            raise ValueError("Ryazhenka splash is missing")
        kernel = root / "mesosphere/out/nintendo_nx_arm64_armv8a/release/mesosphere.bin"
        if entries["mesosphere"] != kernel.read_bytes():
            raise ValueError("Package contains a different kernel build")
        loader = root / "stratosphere/loader/out/nintendo_nx_arm64_armv8a/release/loader.kip"
        if entries["Loader"] != loader.read_bytes():
            raise ValueError("Package contains a different loader build")
        build = root / "stratosphere/ams_mitm/out/nintendo_nx_arm64_armv8a/release"
        if entries["ams_mitm"] != (build / "ams_mitm.kip").read_bytes():
            raise ValueError("Package contains a different ams_mitm build")
        brand = ("%s|RYZ v" + ryazhenka + "|%c").encode("ascii")
        if brand not in (build / "ams_mitm.elf").read_bytes():
            raise ValueError("Compiled version display is missing")

    print("Verified Ryazhenka " + ryazhenka + ": ZIP CRC, package3 versions, 8 KIP hashes, splash, branding and payload")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit("Usage: verify_ryazhenka_release.py RELEASE.zip")
    verify(sys.argv[1])
