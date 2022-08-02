#!/usr/bin/env bash
set -eou pipefail
cmd="clear && ./build/chan-test/chan-test -v -a ${@:-}| ./submodules/c_greatest/contrib/greenest"
eval "$cmd"
