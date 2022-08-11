#!/usr/bin/env bash
# Summary : Create New Test Case Meson Project
#
# Description : Create New Test Case Meson Project
#
# Options :
#
# % test-case-name
# desc="Test Case Name."
# short="t" type="option" variable="TEST_CASE_NAME" default=none
#
# % test-case-enabled
# desc="Test Case Execution Enabled"
# short="e" type="flag" variable="TEST_CASE_ENABLED" value=true default=false
#
# % test-case-install
# desc="Install Test Case Name"
# short="i" type="flag" variable="TEST_CASE_INSTALL" value=true default=false
#
# % repo-dir
# desc="Meson Repository Directory"
# short="r" type="option" variable="REPO_DIR" default=~/repos/c_deps
#
# % tab-completion
# desc="Register Tab Completion."
# short="c" type="flag" variable="tab_completion" value=1 default=0
#
# % test-case-debug-memory
# desc="Test Case Debug Memory Enabled"
# short="M" type="flag" variable="TEST_CASE_DEBUG_MEMORY_ENABLED" value=true default=false
#
# % overwrite-test-case
# desc="Overwrite Test Case"
# short="O" type="flag" variable="OVERWRITE_TEST_CASE" value=true default=false
#
# % test-case-debug
# desc="Debug Mode"
# short="D" type="flag" variable="TEST_CASE_DEBUG_MODE" value=true default=false
#
# % dry-run
# desc="Dry Run Mode"
# short="n" type="flag" variable="DRY_RUN_MODE" value=1 default=0
#
# % debug-mode
# desc="Debug Mode"
# short="d" type="flag" variable="DEBUG_MODE" value=1 default=0
#
. ~/repos/bash-args/init.sh
set -eou pipefail
if [[ "$tab_completion" -eq 1 ]]; then
	$0 _register_completion
	exit
fi
if [[ "$@" != "" ]]; then
	if [[ "$TEST_CASE_NAME" == "none" ]]; then
		TEST_CASE_NAME="$1"
		shift || true
	else
		echo -e "bogus extra args: ${@:-}"
		exit 1
	fi
fi
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [[ "$DRY_RUN_MODE" == 1 || "$DEBUG_MODE" == 1 ]]; then
	echo -e "REPO_DIR=$REPO_DIR"
	echo -e "TEST_CASE_NAME=$TEST_CASE_NAME"
	echo -e "TEST_CASE_DEBUG_MODE=$TEST_CASE_DEBUG_MODE"
	echo -e "TEST_CASE_DEBUG_MEMORY_ENABLED=$TEST_CASE_DEBUG_MEMORY_ENABLED"
fi
############################################################################################################
DEPENDENCIES="c_greatest_dep c_vector_dep c_fsio_dep c_stringfn_dep ansi_codes_dep debug_memory_dep"
INCLUDED_HEADERS="c_greatest/greatest/greatest.h c_fsio/include/fsio.h c_vector/include/vector.h ansi-codes/ansi-codes.h c_stringfn/include/stringfn.h"
############################################################################################################
if [[ "$TEST_CASE_NAME" == "none" ]]; then
	ansi -n --bold --green "Enter Test Case Name:  "
	read TEST_CASE_NAME
fi
source deps-utils.sh
if [[ "$DEBUG_MODE" == 1 ]]; then
	REDIRECT_OUTPUT=/dev/stdout
else
	REDIRECT_OUTPUT=/dev/null
fi
SCRIPTS_DIR="$(pwd)"
J2_BIN="$(command -v jinja2)"
JO_BIN="$(command -v jo)"
JQ_BIN="$(command -v jq)"
MUON_BIN="$(command -v muon)"
UNCRUSTIFY_BIN="$(command -v uncrustify)"
J2_ARGS="--strict --format json"
TEMPLATE_VARS_FILE=$(mktemp)
J2_CMDS="jq < $TEMPLATE_VARS_FILE"
TEST_CASE_NAME="${TEST_CASE_NAME}-test"
TEST_CASE_RENDERED_C_FILE=$(mktemp)
TEST_CASE_RENDERED_H_FILE=$(mktemp)
TEST_CASE_RENDERED_MESON_BUILD_FILE=$(mktemp)
TEST_CASE_NAME_SLUG="$(echo $TEST_CASE_NAME | tr '-' '_' | tr '[A-Z]' '[a-z]')"
JO_ARGS_FILE=$(mktemp)

cd ../.
SCRIPTS_DIR="$(pwd)/scripts"
ETC_DIR="$(pwd)/etc"
TEMPLATES_DIR=$ETC_DIR
MESON_BUILD_DIR=$REPO_DIR/build
TEST_CASE_DIR="${REPO_DIR}/${TEST_CASE_NAME}"

if [[ -d "$TEST_CASE_DIR" && "$OVERWRITE_TEST_CASE" != true ]]; then
	ansi --red --bg-black "Test Case Directory '$TEST_CASE_DIR' Already Exists!"
	ansi --red "       Specify -O or --overwrite-test-case to Overwrite"
	exit 1
fi

UNCRUSTIFY_CFG="$ETC_DIR/uncrustify.cfg"
TEMPLATE_MESON_BUILD="$TEMPLATES_DIR/template-test-case_meson.build.j2"
TEMPLATE_H="$TEMPLATES_DIR/template-test-case_h.j2"
TEMPLATE_C="$TEMPLATES_DIR/template-test-case_c.j2"
MESON_ADD_SUBDIR_CMD="grep -q \"^subdir('$TEST_CASE_NAME')$\" $REPO_DIR/meson.build || echo -e \"subdir('$TEST_CASE_NAME')\" >> $REPO_DIR/meson.build"
MESON_CMDS=" && ( cd $REPO_DIR && $MESON_ADD_SUBDIR_CMD && meson setup --reconfigure $MESON_BUILD_DIR && meson compile -j 10 -C $MESON_BUILD_DIR $TEST_CASE_NAME && meson test --print-errorlogs -v -C $MESON_BUILD_DIR $TEST_CASE_NAME )"
J2_POST_CMDS="$UNCRUSTIFY_BIN -l c -q -c $UNCRUSTIFY_CFG $TEST_CASE_RENDERED_C_FILE $TEST_CASE_RENDERED_H_FILE && muon check $TEST_CASE_RENDERED_MESON_BUILD_FILE && { [[ -d "$TEST_CASE_DIR" ]] || mkdir $TEST_CASE_DIR; } && cp $TEST_CASE_RENDERED_C_FILE $TEST_CASE_DIR/$TEST_CASE_NAME.c && cp $TEST_CASE_RENDERED_H_FILE $TEST_CASE_DIR/$TEST_CASE_NAME.h && cp $TEST_CASE_RENDERED_MESON_BUILD_FILE $TEST_CASE_DIR/meson.build $MESON_CMDS"

prepare_vars_file() {
	echo -n "" >$TEMPLATE_VARS_FILE
	echo -ne " \"TEST_CASE_NAME\"=\"$TEST_CASE_NAME\"" >>$JO_ARGS_FILE
	echo -ne " \"TEST_CASE_NAME_SLUG\"=\"$TEST_CASE_NAME_SLUG\"" >>$JO_ARGS_FILE
	echo -ne " \"TEST_CASE_ENABLED\"=$TEST_CASE_ENABLED" >>$JO_ARGS_FILE
	echo -ne " \"TEST_CASE_DEBUG_MODE\"=$TEST_CASE_DEBUG_MODE" >>$JO_ARGS_FILE
	echo -ne " \"TEST_CASE_DEBUG_MEMORY_ENABLED\"=$TEST_CASE_DEBUG_MEMORY_ENABLED" >>$JO_ARGS_FILE
	echo -ne " \"TEST_CASE_INSTALL\"=$TEST_CASE_INSTALL" >>$JO_ARGS_FILE
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
		echo -ne " \"$K\"=\"$V\"" >>$JO_ARGS_FILE
	done; done
	JO_CMD="$JO_BIN $(cat $JO_ARGS_FILE)"
	eval "$JO_CMD" | $JQ_BIN -Mr >$TEMPLATE_VARS_FILE
	local J2_CMD="$J2_BIN $J2_ARGS -o '$OUT_FILE' '$TEMPLATE_FILE' '$TEMPLATE_VARS_FILE'"
	J2_CMDS+="&& $J2_CMD"
}
prepare_vars_file

EXTRA_TEMPLATE_VARS=
new_j2_cmd $TEST_CASE_RENDERED_MESON_BUILD_FILE "$TEMPLATE_MESON_BUILD" "$EXTRA_TEMPLATE_VARS"
new_j2_cmd $TEST_CASE_RENDERED_H_FILE "$TEMPLATE_H" "$EXTRA_TEMPLATE_VARS"
new_j2_cmd $TEST_CASE_RENDERED_C_FILE "$TEMPLATE_C" "$EXTRA_TEMPLATE_VARS"

if [[ "$DRY_RUN_MODE" == 1 ]]; then
	msg="Generating test case '$(ansi -n --green "$TEST_CASE_NAME")' @ '$(ansi -n --cyan "$TEST_CASE_DIR")' using \n\t$(ansi -n --magenta "$TEMPLATE_MESON_BUILD, $TEMPLATE_H, $TEMPLATE_C")\nWith Commands\n\t'$(ansi -n --red "$J2_CMDS")'"
	echo -e "$msg"
	ansi --yellow --italic "$J2_CMDS && $J2_POST_CMDS"
	exit
fi

eval "$J2_CMDS && $J2_POST_CMDS" >$REDIRECT_OUTPUT

msg="\n\nGenerated, Added to Meson Project, and Tested $(ansi -n --green "$TEST_CASE_NAME") \
    \n  | \tMeson Subdir     :\t$(ansi --green --bg-black --bold -n "$(basename $TEST_CASE_DIR)")\
    \n  | \tMeson Config     :\t$(ansi --magenta-intense --bg-black --bold -n "$(basename $TEST_CASE_DIR)/meson.build")\
    \n  | \tHeader           :\t$(ansi --yellow --bg-black --bold -n "$(basename $TEST_CASE_DIR)/$TEST_CASE_NAME.h")\
    \n  | \tSource           :\t$(ansi --yellow --bg-black --bold -n "$(basename $TEST_CASE_DIR)/$TEST_CASE_NAME.c")\
    \n  | \tSetup            :\t$(ansi --red-intense --bg-black --bold -n "meson setup --reconfigure $(basename $MESON_BUILD_DIR)")\
    \n  | \tCompile          :\t$(ansi --cyan-intense --bg-black --bold -n "meson compile -C $(basename $MESON_BUILD_DIR) $TEST_CASE_NAME")\
    \n  | \tBinary           :\t$(ansi --blue --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME")\
    \n  | \tMeson Test       :\t$(ansi --magenta --bg-black --bold -n "meson test -C $REPO_DIR/build --print-errorlogs -v -C $(basename $MESON_BUILD_DIR) $TEST_CASE_NAME")\
    \n  | \tExecution        :\t$(ansi --cyan --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME -v -a")\
    \n  | \tList Test Cases  :\t$(ansi --red --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME -l")\
    \n  | \tList Test Suites :\t$(ansi --red --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME -L")\
\n\n"
echo -e "$msg"
