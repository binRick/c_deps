#!/usr/bin/env bash
set -eou pipefail
cmd="./scripts/Dbgp-test.sh ${@:-}"
nodemon -w build/dbgp-test/dbgp-test -x sh -- -c "$cmd||true"
