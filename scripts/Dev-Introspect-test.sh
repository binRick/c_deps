#!/usr/bin/env bash
set -eou pipefail
cmd="./Introspect-test.sh"
F="$(find build/introspect* -type f | xargs -I % echo -e "-w '%'" | tr -s '\n' ' ')"
cmd="nodemon $F -x sh -- -c '$cmd||true'"
ansi --yellow --bg-black --italic "$cmd"
eval "$cmd"
