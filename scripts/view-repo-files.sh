#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
set +e
find /tmp/meson-repos-git-status-*.log -type f | sort -u | while read -r f; do
	repo="$(echo $f | tr '-' '\n' | tail -n1 | cut -d'.' -f1)"
	UNTRACKED_FILES="$(cat "$f" | sed -n '/^Untracked files.*$/,/^[[:space:]]*$/p' | egrep -v '^Untracked files|to include in')"
	MODIFIED_FILES="$(cat "$f" | sed -n '/^Changes not staged.*$/,/^[[:space:]]*$/p' | egrep -v '^Untracked files|to include in' | grep modified: | grep -v 'submodules/' | tr -d '[[:blank:]]' | cut -d: -f2 | xargs -I % echo -e "     %")"

	qty_modified="$(echo -e "$MODIFIED_FILES" | wc -l)"
	qty_untracked="$(echo -e "$UNTRACKED_FILES" | wc -l)"

	if [[ "$MODIFIED_FILES" != "$UNTRACKED_FILES" || "" != "" ]]; then
		echo -e "$(ansi --green "$repo")"
	fi
	if [[ "$MODIFIED_FILES" != "" ]]; then
		echo -e "  $(ansi -n --yellow $qty_modified) $(ansi --magenta "Modified Files")"
		echo -e "  $(ansi --cyan "$MODIFIED_FILES\n")"
	fi
	if [[ "$UNTRACKED_FILES" != "" ]]; then
		echo -e "  $(ansi -n --yellow $qty_untracked) $(ansi --magenta "Untracked Files")"
		echo -e "  $(ansi --red "$UNTRACKED_FILES\n")"
	fi
	true
done
