#!/usr/bin/env bash
# Summary : Create New Meson Subdir
#
# Description : Create New Meson Subdir
#
# Options :
#
# % name
# desc="Subdir Name"
# short="t" type="option" variable="SUBDIR_NAME" default=none
#
# % dependencies
# desc="Subdir Dependencies."
# short="x" type="option" variable="SUBDIR_TEST_DEPENDENCIES" default=none
#
# % headers
# desc="Subdir Headers."
# short="h" type="option" variable="SUBDIR_TEST_HEADERS" default=none
#
# % enabled
# desc="Subdir Execution Enabled"
# short="e" type="flag" variable="SUBDIR_TEST_ENABLED" value=true default=false
#
# % installed
# desc="Install Subdir Executable to system on meson install"
# short="i" type="flag" variable="SUBDIR_TEST_INSTALL" value=true default=false
#
# % repo-dir
# desc="Meson Repository Directory"
# short="r" type="option" variable="REPO_DIR" default=~/repos/c_deps
#
# % tab-completion
# desc="Register Tab Completion."
# short="c" type="flag" variable="tab_completion" value=1 default=0
#
# % debug-memory
# desc="Subdir Debug Memory Enabled"
# short="M" type="flag" variable="SUBDIR_TEST_DEBUG_MEMORY_ENABLED" value=true default=false
#
# % overwrite
# desc="Overwrite Subdir"
# short="O" type="flag" variable="OVERWRITE_SUBDIR_TEST" value=true default=false
#
# % enable-subdir-debug-mode
# desc="Debug Mode"
# short="D" type="flag" variable="SUBDIR_TEST_DEBUG_MODE" value=true default=false
#
# % dry-run
# desc="Dry Run Mode"
# short="n" type="flag" variable="DRY_RUN_MODE" value=1 default=0
#
# % debug-mode
# desc="Debug Mode"
# short="d" type="flag" variable="DEBUG_MODE" value=1 default=0
#
. ~/repos/c_deps/scripts/init.sh
set -eou pipefail
if [[ "$tab_completion" -eq 1 ]]; then
	$0 _register_completion
	exit
fi
if [[ "$@" != "" ]]; then
	if [[ "$SUBDIR_NAME" == "none" ]]; then
		SUBDIR_NAME="$1"
		shift || true
	else
		echo -e "bogus extra args: ${@:-}"
		exit 1
	fi
fi
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [[ "$DRY_RUN_MODE" == 1 || "$DEBUG_MODE" == 1 ]]; then
	echo -e "REPO_DIR=$REPO_DIR"
	echo -e "SUBDIR_NAME=$SUBDIR_NAME"
	echo -e "SUBDIR_TEST_DEBUG_MODE=$SUBDIR_TEST_DEBUG_MODE"
	echo -e "SUBDIR_TEST_DEPENDENCIES=$SUBDIR_TEST_DEPENDENCIES"
	echo -e "SUBDIR_TEST_DEBUG_MEMORY_ENABLED=$SUBDIR_TEST_DEBUG_MEMORY_ENABLED"
fi
############################################################################################################
DEPENDENCIES="c_greatest_dep c_vector_dep c_fsio_dep c_stringfn_dep ansi_codes_dep logh_dep timestamp_dep"
INCLUDED_HEADERS="c_greatest/greatest/greatest.h c_fsio/include/fsio.h c_vector/vector/vector.h ansi-codes/ansi-codes.h c_stringfn/include/stringfn.h timestamp/timestamp.h log.h/log.h"
############################################################################################################
if [[ "$SUBDIR_TEST_DEPENDENCIES" != "none" ]]; then
	DEPENDENCIES+=" $SUBDIR_TEST_DEPENDENCIES"
fi

if [[ "$SUBDIR_TEST_HEADERS" != "none" ]]; then
	INCLUDED_HEADERS+=" $SUBDIR_TEST_HEADERS"
fi
############################################################################################################
if [[ "$SUBDIR_NAME" == "none" ]]; then
	ansi -n --bold --green "Enter Subdir Name:  "
	read SUBDIR_NAME
fi
source deps-utils.sh
EXTRA_TEMPLATE_VARS=
EXPECTED_LINES=130
SCRIPTS_DIR="$(pwd)"
J2_BIN="$(command -v jinja2)"
BASH_BIN="$(command -v bash)"
JO_BIN="$(command -v jo)"
JQ_BIN="$(command -v jq)"
PV_BIN="$(command -v pv)"
ANSI_BIN="$(command -v ansi)"
if [[ "$DEBUG_MODE" == 1 ]]; then
	REDIRECT_OUTPUT=" > /dev/stdout"
else
	REDIRECT_OUTPUT=" | $PV_BIN -e -p -t -s $EXPECTED_LINES -l > /dev/null"
fi
UNCRUSTIFY_BIN="$(command -v uncrustify)"
J2_ARGS="--strict --format json"
TEMPLATE_VARS_FILE=$(mktemp)
J2_CMDS="$JQ_BIN -Mrc < $TEMPLATE_VARS_FILE >/dev/null"
SUBDIR_NAME="${SUBDIR_NAME}-test"
SUBDIR_TEST_RENDERED_C_FILE=$(mktemp)
SUBDIR_TEST_RENDERED_H_FILE=$(mktemp)
SUBDIR_TEST_RENDERED_MESON_BUILD_FILE=$(mktemp)
SUBDIR_NAME_SLUG="$(echo $SUBDIR_NAME | tr '-' '_' | tr '[A-Z]' '[a-z]')"
JO_ARGS_FILE=$(mktemp)

cd ../.
SCRIPTS_DIR="$(pwd)/scripts"
ETC_DIR="$(pwd)/etc"
TEMPLATES_DIR=$ETC_DIR
MESON_BUILD_DIR=$REPO_DIR/build
SUBDIR_TEST_DIR="${REPO_DIR}/${SUBDIR_NAME}"

if [[ -d "$SUBDIR_TEST_DIR" && "$OVERWRITE_SUBDIR_TEST" != true ]]; then
	ansi --red --bg-black "Subdir Directory '$SUBDIR_TEST_DIR' Already Exists!"
	ansi --red "       Specify -O or --overwrite to Overwrite"
	exit 1
fi

UNCRUSTIFY_CFG="$ETC_DIR/uncrustify.cfg"
TEMPLATE_MESON_BUILD="$TEMPLATES_DIR/template-subdir-test_meson.build.j2"
TEMPLATE_H="$TEMPLATES_DIR/template-subdir-test_h.j2"
TEMPLATE_C="$TEMPLATES_DIR/template-subdir-test_c.j2"
MESON_ADD_SUBDIR_CMD="grep -q \"^subdir('$SUBDIR_NAME')$\" $REPO_DIR/meson.build || echo -e \"subdir('$SUBDIR_NAME')\" >> $REPO_DIR/meson.build"
MESON_CMDS=" && ( cd $REPO_DIR && $MESON_ADD_SUBDIR_CMD && meson setup --reconfigure $MESON_BUILD_DIR && meson compile -j 10 -C $MESON_BUILD_DIR $SUBDIR_NAME && meson test --print-errorlogs -v -C $MESON_BUILD_DIR $SUBDIR_NAME )"
J2_POST_CMDS="$UNCRUSTIFY_BIN --no-backup -l c -q -c $UNCRUSTIFY_CFG $SUBDIR_TEST_RENDERED_C_FILE $SUBDIR_TEST_RENDERED_H_FILE && muon check $SUBDIR_TEST_RENDERED_MESON_BUILD_FILE && { [[ -d "$SUBDIR_TEST_DIR" ]] || mkdir $SUBDIR_TEST_DIR; } && cp $SUBDIR_TEST_RENDERED_C_FILE $SUBDIR_TEST_DIR/$SUBDIR_NAME.c && cp $SUBDIR_TEST_RENDERED_H_FILE $SUBDIR_TEST_DIR/$SUBDIR_NAME.h && cp $SUBDIR_TEST_RENDERED_MESON_BUILD_FILE $SUBDIR_TEST_DIR/meson.build $MESON_CMDS"

prepare_vars_file() {
	rm $JO_ARGS_FILE
	echo -ne " \"SUBDIR_NAME\"=\"$SUBDIR_NAME\"" >>$JO_ARGS_FILE
	echo -ne " \"SUBDIR_NAME_SLUG\"=\"$SUBDIR_NAME_SLUG\"" >>$JO_ARGS_FILE
	echo -ne " \"SUBDIR_TEST_ENABLED\"=$SUBDIR_TEST_ENABLED" >>$JO_ARGS_FILE
	echo -ne " \"SUBDIR_TEST_DEBUG_MODE\"=$SUBDIR_TEST_DEBUG_MODE" >>$JO_ARGS_FILE
	echo -ne " \"SUBDIR_TEST_DEBUG_MEMORY_ENABLED\"=$SUBDIR_TEST_DEBUG_MEMORY_ENABLED" >>$JO_ARGS_FILE
	echo -ne " \"SUBDIR_TEST_INSTALL\"=$SUBDIR_TEST_INSTALL" >>$JO_ARGS_FILE
	echo -ne " \"DEPENDENCIES\"=\"$DEPENDENCIES\"" >>$JO_ARGS_FILE
	echo -ne " \"INCLUDED_HEADERS\"=\"$INCLUDED_HEADERS\"" >>$JO_ARGS_FILE
}
new_j2_cmd() {
	local OUT_FILE="$1"
	shift
	local TEMPLATE_FILE="$1"
	shift
	local TEMPLATE_VARS="$@"
	local JO_CMD="$JO_BIN"

	echo -e "$TEMPLATE_VARS" | tr '|' '\n' | while read -r KV; do echo -e "$KV" | while IFS='=' read -r K V; do
		[[ "$K" == "" ]] && continue
		echo -ne " \"$K\"=\"$V\"" >>$JO_ARGS_FILE
	done; done
	JO_CMD="$JO_BIN $(cat $JO_ARGS_FILE)"
	eval "$JO_CMD" | $JQ_BIN -Mr >$TEMPLATE_VARS_FILE
	local J2_CMD="$J2_BIN $J2_ARGS -o '$OUT_FILE' '$TEMPLATE_FILE' '$TEMPLATE_VARS_FILE'"
	J2_CMDS+="&& $J2_CMD"
}
prepare_vars_file

new_j2_cmd $SUBDIR_TEST_RENDERED_MESON_BUILD_FILE "$TEMPLATE_MESON_BUILD" "$EXTRA_TEMPLATE_VARS"
new_j2_cmd $SUBDIR_TEST_RENDERED_H_FILE "$TEMPLATE_H" "$EXTRA_TEMPLATE_VARS"
new_j2_cmd $SUBDIR_TEST_RENDERED_C_FILE "$TEMPLATE_C" "$EXTRA_TEMPLATE_VARS"

if [[ "$DRY_RUN_MODE" == 1 || "$DEBUG_MODE" == 1 ]]; then
	msg="Generating Subdir test files '$(ansi -n --green "$SUBDIR_NAME")' @ '$(ansi -n --cyan "$SUBDIR_TEST_DIR")' using \n\t$(ansi -n --magenta "$TEMPLATE_MESON_BUILD, $TEMPLATE_H, $TEMPLATE_C")\nWith Commands\n\t'$(ansi -n --red "$J2_CMDS")'"
	echo -e "$msg"
	eval $JQ_BIN -rC <$TEMPLATE_VARS_FILE
	ansi --yellow --italic "$J2_CMDS && $J2_POST_CMDS"
	if [[ "$DRY_RUN_MODE" == 1 ]]; then exit; fi
fi

$BASH_BIN -ec "$J2_CMDS && $J2_POST_CMDS $REDIRECT_OUTPUT"

msg="\n\nGenerated, Added to Meson Project, and Tested $(ansi -n --green "$SUBDIR_NAME") \
    \n  | \tMeson Subdir     :\t$(ansi --green --bg-black --bold -n "$(basename $SUBDIR_TEST_DIR)")\
    \n  | \tMeson Config     :\t$(ansi --magenta-intense --bg-black --bold -n "$(basename $SUBDIR_TEST_DIR)/meson.build")\
    \n  | \tHeader           :\t$(ansi --yellow --bg-black --bold -n "$(basename $SUBDIR_TEST_DIR)/$SUBDIR_NAME.h")\
    \n  | \tSource           :\t$(ansi --yellow --bg-black --bold -n "$(basename $SUBDIR_TEST_DIR)/$SUBDIR_NAME.c")\
    \n  | \tSetup            :\t$(ansi --red-intense --bg-black --bold -n "meson setup --reconfigure $(basename $MESON_BUILD_DIR)")\
    \n  | \tCompile          :\t$(ansi --cyan-intense --bg-black --bold -n "meson compile -C $(basename $MESON_BUILD_DIR) $SUBDIR_NAME")\
    \n  | \tBinary           :\t$(ansi --blue --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$SUBDIR_NAME/$SUBDIR_NAME")\
    \n  | \tMeson Test       :\t$(ansi --magenta --bg-black --bold -n "meson test -C $REPO_DIR/build --print-errorlogs -v -C $(basename $MESON_BUILD_DIR) $SUBDIR_NAME")\
    \n  | \tExecution        :\t$(ansi --cyan --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$SUBDIR_NAME/$SUBDIR_NAME -v -a")\
    \n  | \tList Test Cases  :\t$(ansi --red --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$SUBDIR_NAME/$SUBDIR_NAME -l")\
    \n  | \tList Test Suites :\t$(ansi --red --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$SUBDIR_NAME/$SUBDIR_NAME -L")\
\n\n"
echo -e "$msg"
