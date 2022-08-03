#!/usr/bin/env bash
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TEST_SUITE="${1:-s_path_module}"
THEME="gruvbox-dark"
cd ../.
SRC=deps-test/deps-test.c
cmd="cat -n $SRC | sed -n '/^[[:space:]][[:space:]][0-9].*[[:space:]].*SUITE(${TEST_SUITE}).*{/,/^[[:space:]].*[0-9].*[[:space:]].*}/p'"

eval "$cmd" | bat -H 1:1 --file-name "$(ansi -n --green --italic $SRC) $(ansi -n --bold --red '->') $(ansi -n --white Test Suite) $(ansi -n --bold --red '->') $(ansi --blue --bold $TEST_SUITE)" --color always --language C --italic-text always --decorations always --theme "$THEME" --style=plain,header,header-filename,grid --wrap=auto

#-f --language C --italic-text always --theme "Monokai Extended"
