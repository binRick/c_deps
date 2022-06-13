#!/usr/bin/env bash
set -eou pipefail
cmd="./Chan-test.sh ${@:-}"
nodemon -w build/chan-test/chan-test -x sh -- -c "$cmd||true"
