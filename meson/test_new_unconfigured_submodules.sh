#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"

(./ls_unconfigured_submodules.sh | shuf | head -n 1000 | xargs -I % ./new_dep.sh %) 2>&1
