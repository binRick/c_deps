#!/usr/bin/env bash
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TEST_CASE="${1:-t_path_module}"
THEME="gruvbox-light"
THEME="1337"
cd ../.
SRC=deps-test/deps-test.c
cmd="cat $SRC | sed -n '/^TEST ${TEST_CASE}(.*$/,/^}$/p'"

eval "$cmd" | bat -H 1:1 --file-name "$(ansi -n --green --italic $SRC) $(ansi -n --bold --red '->') $(ansi -n --white Test Case) $(ansi -n --bold --red '->') $(ansi --magenta --bold $TEST_CASE)" --color always --language C --italic-text always --decorations always --theme "$THEME" --style=plain,header,header-filename,grid --wrap=auto
