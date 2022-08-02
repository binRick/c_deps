#!/usr/bin/env bash
set -eou pipefail
cmd="ansi --reset --down=10 && ./build/dbgp-test/dbgp-test -v -a ${@:-}| ./submodules/c_greatest/contrib/greenest"
eval "$cmd"
