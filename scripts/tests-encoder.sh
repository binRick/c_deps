#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source deps-utils.sh
cd ../.
rm .tests-*.log

make tests-suite-tests

while read -r SUITE; do
	grep "^\* Suite $SUITE:" -A 999 .tests-list.log | gsed -n "/^* Suite ${SUITE}:\$/,/^* Suite /p" |
		grep -v '^* Suite ' |
		grep '^[[:space:]] ' |
		gsed 's/[[:space:]]//g' | sort -u | grep -v '^$' |
		tee .test-suite__${SUITE}.log >/dev/null

	jo "binary"="deps-test" suite="${SUITE}" tests="$(jo -a $(\cat .test-suite__${SUITE}.log))"

done < <(cat .tests-suites.log)
