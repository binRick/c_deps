#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"

DEPS_BASE="$(pwd)/deps"

NAME="$1"
TEMPLATE="${TEMPLATE:-templates/meson.build-library-dep}"
INSTALL="${INSTALL:-false}"
TYPE="${TYPE:-static}"
DEPS="${DEPS:-}"
MB=$DEPS_BASE/$NAME/meson.build

#[[ -f "$MB" ]] && exit 1
[[ -d ../submodules/$NAME ]] || exit 1
MD=3
submodule_local_headers() {
  find -L ../submodules/$NAME -maxdepth $MD -type f -name "*.h"|sort -u|format_file|gsed 's|../../../submodules/||g'|egrep -v '/test\.'
}
submodule_system_headers() {
  echo
#  find ../submodules/$NAME -type f -name "*.h"|sort -u
}
submodule_files() {
	{
		find -L ../submodules/$NAME -maxdepth $MD -type f -name "*.c"
	} | sort -u
}

inc_dirs() {
	{
		find ../submodules/$NAME -maxdepth $MD -type d
		submodule_files | filter_files | xargs -I % dirname %
		printf "../../../submodules/%s\n" "$NAME"
	} | sort -u
}

blacklist() {
	egrep -iv "examples|example|fuzz|compat|/\.|cmake|/$NAME/deps|documentation|license|docs|demo|/man$|/subprojects$|/.*\.dSYM|/build|test|thirdparty|/data|/tools|deprecated|/assets|bench|/$NAME/subprojects|/vendor|/scripts|/etc|windows|/ext|/t$|/t/|third_party|benchmark|scripts|/deps$|/utils$|xcodeproj|doxygen|docs|/$NAME/meson|^$|/mk$|/mk/|/util/|/po$|visualc|/$NAME/target/"
}

filter_dirs() {
    {
	egrep -v "/test.*|.*[0-9].*|/$NAME/submodules" |
		egrep "/$NAME|$NAME/[a-z].*$|$NAME/[A-Z].*$" |
		egrep "/$NAME$|/$NAME/.*$" |
		blacklist
    echo "../submodules/$NAME"
    }|sort -u
}

filter_files() {
	egrep -v '/test/|/main.c$|/tests/|/.*test.*' |
		blacklist
}

format_file() {
	while read -r f; do
		printf "  '../../%s',\n" "$f"
	done
}

submodule_inc_dirs() {
	inc_dirs | filter_dirs | format_file
}

submodule_src_files() {
	submodule_files | filter_files | format_file
}

(
	ansi --green --reverse --bold "$NAME"
	ansi --yellow --italic "$(submodule_inc_dirs)"
	ansi --blue --bold "$(submodule_src_files)"
) >&2

[[ -d "$(dirname "$MB")" ]] || mkdir -p "$(dirname "$MB")"
tf=$(mktemp)
cp $TEMPLATE $tf
gsed -i "s|__LOCAL_HEADERS__|\$LOCAL_HEADERS|g" $tf
gsed -i "s|__SYSTEM_HEADERS__|\$SYSTEM_HEADERS|g" $tf
gsed -i "s|__NAME__|$NAME|g" $tf
gsed -i "s|__TYPE__|$TYPE|g" $tf
gsed -i "s|__SRCS__|\${__SRCS__}|g" $tf
gsed -i "s|__DIRS__|\${__DIRS__}|g" $tf
gsed -i "s|__INSTALL__|$INSTALL|g" $tf
gsed -i "s|__DEPS__|$DEPS|g" $tf

render_template() {
	(
		export __DIRS__="$(submodule_inc_dirs)"
		export __SRCS__="$(submodule_src_files)"
		export SYSTEM_HEADERS="$(submodule_system_headers)"
		export LOCAL_HEADERS="$(submodule_local_headers)"
		eval "echo -e \"$(\cat "$tf")\""
	)
}

if [[ ! -f "$MB" ]]; then
  render_template > $MB
  ansi --green --bold "$MB created"

else
  F="$(render_template)"

  {
    echo -e ""
    ansi --blue --bold --italic "$F"
    echo -e ""
  } >&2

  echo -e "$F"

fi

MESON_BUILD_SUBDIR_LINE="subdir('deps/$NAME')"

if ! grep -q "$MESON_BUILD_SUBDIR_LINE" meson.build; then
  printf "%s\n" "$MESON_BUILD_SUBDIR_LINE" >> meson.build
fi
