#!/usr/bin/env bash
#
# apply_version.sh — Ryazhenka
#
# EN: Reads the version from version.txt and injects "Ryazhenka v<version>" into the
#     on-console display-version source. Run automatically by CI before building, and
#     can be run manually after editing version.txt.
# RU: Читает версию из version.txt и подставляет "Ryazhenka v<версия>" в исходник
#     строки версии, показываемой на консоли. Запускается автоматически в CI перед
#     сборкой; можно запустить вручную после правки version.txt.
#
# Usage: scripts/apply_version.sh
# It also prints the bare version to stdout so CI can capture it for the release name.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSION_FILE="${REPO_ROOT}/version.txt"
TARGET="${REPO_ROOT}/stratosphere/ams_mitm/source/set_mitm/setsys_mitm_service.cpp"

if [[ ! -f "${VERSION_FILE}" ]]; then
    echo "error: version.txt not found at ${VERSION_FILE}" >&2
    exit 1
fi

# First non-comment, non-blank line, trimmed.
VERSION="$(grep -vE '^\s*(#|$)' "${VERSION_FILE}" | head -n1 | tr -d '[:space:]')"
# Strip an optional leading "v".
VERSION="${VERSION#v}"

if [[ -z "${VERSION}" ]]; then
    echo "error: no version found in ${VERSION_FILE}" >&2
    exit 1
fi

if [[ ! -f "${TARGET}" ]]; then
    echo "error: target source not found at ${TARGET}" >&2
    exit 1
fi

# Replace the package_version string. The buffer is sized [64]; keep the value short.
sed -i -E "s/(char package_version\[64\] = \")Ryazhenka v[^\"]*(\";)/\1Ryazhenka v${VERSION}\2/" "${TARGET}"

if ! grep -q "Ryazhenka v${VERSION}\"" "${TARGET}"; then
    echo "error: failed to inject version into ${TARGET}" >&2
    exit 1
fi

echo "applied Ryazhenka v${VERSION} -> ${TARGET}" >&2
# Bare version on stdout for CI.
echo "${VERSION}"
