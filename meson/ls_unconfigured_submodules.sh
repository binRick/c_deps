#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

comm -23 <(./ls_submodules.sh) <(./ls_library_deps.sh)|sort -u
