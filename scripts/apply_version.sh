#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSION_FILE="${REPO_ROOT}/version.txt"
TARGET="${REPO_ROOT}/stratosphere/ams_mitm/source/set_mitm/setsys_mitm_service.cpp"

[[ -f "${VERSION_FILE}" ]] || { echo "error: version.txt not found" >&2; exit 1; }
[[ -f "${TARGET}" ]] || { echo "error: target source not found" >&2; exit 1; }
VERSION="$(grep -vE '^\s*(#|$)' "${VERSION_FILE}" | head -n1 | tr -d '[:space:]')"
VERSION="${VERSION#v}"
[[ -n "${VERSION}" ]] || { echo "error: no version found" >&2; exit 1; }
[[ "${VERSION}" =~ ^[0-9]+(\.[0-9]+){1,3}([-.][0-9A-Za-z]+)?$ ]] || { echo "error: invalid version format" >&2; exit 1; }
[[ ${#VERSION} -le 11 ]] || { echo "error: version exceeds the 11-character display limit" >&2; exit 1; }

sed -i -E "s/(constexpr const char package_version\[\] = \")[^\"]*(\";)/\1${VERSION}\2/" "${TARGET}"
grep -Fq "constexpr const char package_version[] = \"${VERSION}\";" "${TARGET}" || { echo "error: compact package version literal not found" >&2; exit 1; }
echo "applied Ryazhenka version ${VERSION}" >&2
echo "${VERSION}"
