#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

egrep 'library\(' deps/*/meson.build | cut -d: -f1 | xargs -I % dirname % | xargs -I % basename % | sort -u
