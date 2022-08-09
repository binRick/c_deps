#!/usr/bin/env bash
set -eou pipefail
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd ../../../.

./build/deps-test/deps-test -l | grep '^[[:space:]] t_' | tr -d ' ' | sort -u
