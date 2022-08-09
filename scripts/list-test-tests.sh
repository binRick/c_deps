#!/usr/bin/env bash
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TEST_FILE="${1:-deps-test}"
cd ../../../.
SRC="$TEST_FILE/${TEST_FILE}.c"
cmd="grep '^TEST ' $SRC|cut -d' ' -f2|cut -d'(' -f1|sort -u"

eval "$cmd"
