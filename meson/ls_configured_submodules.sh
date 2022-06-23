#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

egrep 'submodules/' ./deps/*/meson.build | egrep -o 'submodules/[^"].*/' | cut -d'/' -f2 | sort -u
