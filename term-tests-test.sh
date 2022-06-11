#!/usr/bin/env bash
set -eou pipefail
nodemon  -V -I -w ./build -x sh -- -c 'reset; ./build/term-tests-test/term-tests-test'
#2>.err'
