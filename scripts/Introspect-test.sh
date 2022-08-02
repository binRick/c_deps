#!/usr/bin/env bash
set -eou pipefail
cmd="./build/introspect-test/introspect-test  -t t_introspect_iterate -v -a ${@:-}| ./submodules/c_greatest/contrib/greenest"
eval "$cmd"
