#!/usr/bin/env bash
set -eou pipefail
BUILD_LOG="${BUILD_LOG:-$(pwd)/build/build.log}"
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ansi --save-palette -n
vterm-ctrl altscreen on
clear
vterm-ctrl title "Warnings Report"
kfc -p liquidcarbontransparent >/dev/tty 2>/dev/null
trap "vterm-ctrl title '';vterm-ctrl altscreen off;ansi --restore-palette" EXIT

while read -r l; do
	IFS=: read -r file line row _x _warning <<<"$l"
	IFS='[' read -r warning ignore_switch <<<"$_warning"
	if echo "$file" | grep -q '\/submodules\/'; then continue; fi
	dir="$(dirname $file | gsed 's|../||g' | gsed 's|./||g')"
	filename="$(basename $file | gsed 's|./||g')"
	[[ "$dir" != "." ]] && filename="$dir/$filename"
	saycmd="$((10 + ${#filename} + ${#line}))"
	saycmd="$((60 - $saycmd))"
	SPACES="$(perl -E "say ' ' x $saycmd")"
	_header="$(echo -e "$(ansi --yellow -n $filename) $(ansi -n --cyan $line)${SPACES}$(ansi -n --red --italic "$warning")")"
	printf "%s\n" "$_header"
done < <(grep 'warning:' $BUILD_LOG) | bat --style=plain --theme=ansi
