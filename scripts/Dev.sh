#!/usr/bin/env bash
set -eou pipefail
cmd="$2"
cmd="nodemon -w './build' -x sh -- -c '$cmd||true'"
eval "$cmd"
