#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEP=$1

get_local_header_files() {
	muon fmt ../meson/deps/$DEP/meson.build | gsed -n "/_local_headers = \[$/,/\]/p" | grep "'" | cut -d"'" -f2 | sort -u
}

get_local_header_files | while read -r f; do
	printf "#include \"%s\"\n" "$f"
done
