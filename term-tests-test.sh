#!/usr/bin/env bash
set -eou pipefail

as_off(){
    vterm-ctrl altscreen off
    ansi -n --restore-palette
    vterm-ctrl cursor on
    ansi -n --cursor-color-yellow
    ansi -n --selection-background-color-yellow
    ansi -n --selection-foreground-color-black
    ansi --green --bg-black --italic "Altscreen disabled"
}
as_on(){
    ansi --save-palette
    vterm-ctrl altscreen on
    vterm-ctrl cursor off
    vterm-ctrl curshape block
    ansi --cursor-color-green
    kfc -s vscode
    trap as_off EXIT
}



cmd="nodemon --delay .01 -I \
    -e c \
    -w .trigger.c \
    -w ./build/term-tests-test/term-tests-test \
    -x ./build/term-tests-test/term-tests-test \
"
#ansi --yellow --italic --bg-black "$cmd"

as_on >/dev/null 2>&1
eval "$cmd" 2>.err
