#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

find deps/*/* -type f -name meson.build | xargs -I % dirname % | xargs -I % basename % | sort -u
