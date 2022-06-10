#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source deps-utils.sh
cd ../.

main() {
	clear
	if [[ "$@" != "" ]]; then
		eval "$@"
	else
		ansi --red --bg-black --bold "No Function Selected. Available functions:"
		while read -r fxn; do
			echo -ne "\t"
			ansi --red --italic --underline "$fxn"
		done < <(get_deps_fxns)
	fi
}

main "${@:-}"
