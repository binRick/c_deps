#!/usr/bin/env bash
# Summary : My first bash script using bash-args.
#
# Description : This takes a command as argument, 
#               register tab completion: eval \$(test.sh _register_completion)
#
# Argument : command
#
# Options :
#
# % option1
# desc="option1 desc."
# short="o" type="option" variable="option1" value=1 default=0
#
# % flag1
# desc="flag1 desc."
# short="f" type="flag" variable="flag1" value=1 default=0
#
# % tab-completion
# desc="Register Tab Completion."
# short="c" type="flag" variable="tab_completion" value=1 default=0
#
# % dry-run
# desc="Don't execute, just print."
# short="n" type="flag" variable="dry_run" value=1 default=0
#
# % directory
# desc="The directory in which to run the command."
# short="d" type="option" variable="directory" default="$(pwd)"
#

. ~/repos/bash-args/init.sh
# After sourcing the script, you can use the $directory and the $dry_run
# variables to get the values of the options typed (or not) in the command line.
# The other arguments are available as standard bash arguments $1, $2, etc.

set -eou pipefail
if [[ "$tab_completion" -eq 1 ]]; then
    $0 _register_completion
    exit
fi
if [[ "$dry_run" -eq 1 ]]; then
    echo dry run
    exit
fi

    echo -e "flag1=$flag1"
    echo -e "option1=$option1"
    echo -e "directory=$directory"
    if [[ "$@" != "" ]]; then
        echo -e "extra args: ${@:-}"
    fi

############################################################################################################
DEPENDENCIES="c_greatest_dep c_vector_dep c_fsio_dep c_stringfn_dep ansi_codes_dep"
INCLUDED_HEADERS="c_greatest/greatest/greatest.h c_fsio/include/fsio.h c_vector/include/vector.h ansi-codes/ansi-codes.h c_stringfn/include/stringfn.h"
############################################################################################################
DEBUG_MODE=${DEBUG_MODE:-0}
TEST_CASE_NAME="${1:-}"
if [[ "$TEST_CASE_NAME" == "" ]]; then
	ansi -n --bold --green "Enter Test Case Name:  "
	read TEST_CASE_NAME
fi
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source deps-utils.sh
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
echo -n "" >$JO_ARGS_FILE
TEST_CASE_ENABLED=false
TEST_CASE_ENABLED=true
TEST_CASE_INSTALL=true
TEST_CASE_INSTALL=false
TEST_CASE_DEBUG_MODE=false
TEST_CASE_DEBUG_MEMORY_ENABLED=false
TEST_CASE_DEBUG_MEMORY_ENABLED=true
TEST_CASE_DEBUG_MODE=true

cd ../.
SCRIPTS_DIR="$(pwd)/scripts"
ETC_DIR="$(pwd)/etc"
TEMPLATES_DIR=$ETC_DIR
REPO_DIR="$(pwd)"
MESON_BUILD_DIR=$REPO_DIR/build

UNCRUSTIFY_CFG="$ETC_DIR/uncrustify.cfg"
TEST_CASE_DIR="${REPO_DIR}/${TEST_CASE_NAME}"
TEMPLATE_MESON_BUILD="$TEMPLATES_DIR/template-test-case_meson.build.j2"
TEMPLATE_H="$TEMPLATES_DIR/template-test-case_h.j2"
TEMPLATE_C="$TEMPLATES_DIR/template-test-case_c.j2"
MESON_ADD_SUBDIR_CMD="grep -q \"^subdir('$TEST_CASE_NAME')$\" meson.build || echo -e \"subdir('$TEST_CASE_NAME')\" >> meson.build"
MESON_CMDS=" && $MESON_ADD_SUBDIR_CMD && meson setup --reconfigure $MESON_BUILD_DIR && meson compile -j 10 -C $MESON_BUILD_DIR $TEST_CASE_NAME && meson test --print-errorlogs -v -C $MESON_BUILD_DIR $TEST_CASE_NAME && true"
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
EXTRA_VARS="var1=y|var2=123|var3=true|var4=['abc']"
new_j2_cmd $TEST_CASE_RENDERED_MESON_BUILD_FILE "$TEMPLATE_MESON_BUILD" "$EXTRA_VARS"
new_j2_cmd $TEST_CASE_RENDERED_H_FILE "$TEMPLATE_H" "$EXTRA_VARS"
new_j2_cmd $TEST_CASE_RENDERED_C_FILE "$TEMPLATE_C" "$EXTRA_VARS"


if [[ "$DEBUG_MODE" == 1 ]]; then
    msg="Generating test case '$(ansi -n --green "$TEST_CASE_NAME")' @ '$(ansi -n --cyan "$TEST_CASE_DIR")' using \n\t$(ansi -n --magenta "$TEMPLATE_MESON_BUILD, $TEMPLATE_H, $TEMPLATE_C")\nWith Commands\n\t'$(ansi -n --red "$J2_CMDS")'"
    echo -e "$msg"
    ansi --yellow --italic "$J2_CMDS && $J2_POST_CMDS"
    exit
fi
eval "$J2_CMDS && $J2_POST_CMDS"

msg="\n\nGenerated, Added to Meson Project, and Tested $(ansi -n --green "$TEST_CASE_NAME") \
    \n  | \tMeson Subdir     :\t$(ansi --green --bg-black --bold -n "$(basename $TEST_CASE_DIR)")\
    \n  | \tMeson Config     :\t$(ansi --magenta-intense --bg-black --bold -n "$(basename $TEST_CASE_DIR)/meson.build")\
    \n  | \tHeader           :\t$(ansi --yellow --bg-black --bold -n "$(basename $TEST_CASE_DIR)/$TEST_CASE_NAME.h")\
    \n  | \tSource           :\t$(ansi --yellow --bg-black --bold -n "$(basename $TEST_CASE_DIR)/$TEST_CASE_NAME.c")\
    \n  | \tSetup            :\t$(ansi --red-intense --bg-black --bold -n "meson setup --reconfigure $(basename $MESON_BUILD_DIR)")\
    \n  | \tCompile          :\t$(ansi --cyan-intense --bg-black --bold -n "meson compile -C $(basename $MESON_BUILD_DIR) $TEST_CASE_NAME")\
    \n  | \tBinary           :\t$(ansi --blue --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME")\
    \n  | \tMeson Test       :\t$(ansi --magenta --bg-black --bold -n "meson test -C build --print-errorlogs -v -C $(basename $MESON_BUILD_DIR) $TEST_CASE_NAME")\
    \n  | \tExecution        :\t$(ansi --cyan --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME -v -a")\
    \n  | \tList Test Cases  :\t$(ansi --red --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME -l")\
    \n  | \tList Test Suites :\t$(ansi --red --bg-black --bold -n "$(basename $MESON_BUILD_DIR)/$TEST_CASE_NAME/$TEST_CASE_NAME -L")\
\n\n"
echo -e "$msg"
