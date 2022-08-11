#!/usr/bin/env bash
set -eou pipefail
REPO_DIR="$(pwd)"
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source deps-utils.sh
SCRIPTS_DIR="$(pwd)"
J2_BIN="$(command -v jinja2)"
JO_BIN="$(command -v jo)"
JQ_BIN="$(command -v jq)"
J2_ARGS="--strict --format json"
TEMPLATE_VARS_FILE=$(mktemp)
TEMPLATE_VARS_FILE=/tmp/vars.json
J2_CMDS="jq < $TEMPLATE_VARS_FILE"


cd ../.
DEPENDENCIES="greatest_dep c_vector_dep c_fsio_dep c_stringfn_dep debug_memory"
INCLUDED_HEADERS="greatest/greatest.h"
TEMPLATES_DIR="$(pwd)/etc"
TEST_CASE_NAME="${1:-}"
TEST_CASE_NAME="${TEST_CASE_NAME}-test"
TEST_CASE_DIR="${REPO_DIR}/${TEST_CASE_NAME}"
TEST_CASE_NAME_SLUG="$(echo $TEST_CASE_NAME|tr '-' '_'|tr '[A-Z]' '[a-z]')"
TEMPLATE_MESON_BUILD="$TEMPLATES_DIR/template-test-case_meson.build.j2"
TEMPLATE_H="$TEMPLATES_DIR/template-test-case_h.j2"
TEMPLATE_C="$TEMPLATES_DIR/template-test-case_c.j2"
JO_ARGS_FILE=$(mktemp)
JO_ARGS_FILE=/tmp/jo.args
TEST_CASE_ENABLED=false
TEST_CASE_ENABLED=true
TEST_CASE_INSTALL=true
TEST_CASE_INSTALL=false
TEST_CASE_DEBUG_MODE=false
TEST_CASE_DEBUG_MEMORY_ENABLED=false
TEST_CASE_DEBUG_MEMORY_ENABLED=true
TEST_CASE_DEBUG_MODE=true
echo -n "" > $JO_ARGS_FILE


if [[ "$TEST_CASE_NAME" == "" ]]; then
    ansi -n --bold --green "Enter Test Case Name:  "
    read TEST_CASE_NAME
fi

prepare_vars_file(){
    echo -n "" > $TEMPLATE_VARS_FILE
    echo -ne " \"TEST_CASE_NAME\"=\"$TEST_CASE_NAME\"" >> $JO_ARGS_FILE
    echo -ne " \"TEST_CASE_NAME_SLUG\"=\"$TEST_CASE_NAME_SLUG\"" >> $JO_ARGS_FILE
    echo -ne " \"TEST_CASE_ENABLED\"=$TEST_CASE_ENABLED" >> $JO_ARGS_FILE
    echo -ne " \"TEST_CASE_DEBUG_MODE\"=$TEST_CASE_DEBUG_MODE" >> $JO_ARGS_FILE
    echo -ne " \"TEST_CASE_DEBUG_MEMORY_ENABLED\"=$TEST_CASE_DEBUG_MEMORY_ENABLED" >> $JO_ARGS_FILE
    echo -ne " \"TEST_CASE_INSTALL\"=$TEST_CASE_INSTALL" >> $JO_ARGS_FILE
    echo -ne " \"DEPENDENCIES\"=\"$DEPENDENCIES\"" >> $JO_ARGS_FILE
    echo -ne " \"INCLUDED_HEADERS\"=\"$INCLUDED_HEADERS\"" >> $JO_ARGS_FILE
}
new_j2_cmd(){
    local OUT_FILE="$1"; shift
    local TEMPLATE_FILE="$1"; shift
    local TEMPLATE_VARS="$@"
    local JO_CMD="$JO_BIN"

    echo -e "$TEMPLATE_VARS"|tr '|' '\n'|while read -r KV; do echo "$KV"|while IFS='=' read -r K V; do 
        echo -ne " \"$K\"=\"$V\"" >> $JO_ARGS_FILE
    done;done
    cat $JO_ARGS_FILE
    JO_CMD="$JO_BIN $(cat $JO_ARGS_FILE)"
    echo -e "$JO_CMD"
    eval "$JO_CMD"|$JQ_BIN -Mr > $TEMPLATE_VARS_FILE
    local J2_CMD="$J2_BIN $J2_ARGS -o '$OUT_FILE' '$TEMPLATE_FILE' '$TEMPLATE_VARS_FILE'"
    J2_CMDS+="&& $J2_CMD"
}
prepare_vars_file
new_j2_cmd "test-meson.build" "$TEMPLATE_MESON_BUILD" "x=y|a=123"
new_j2_cmd "test-h" "$TEMPLATE_H" "x=y|a=123"
new_j2_cmd "test-c" "$TEMPLATE_C" "x=y|a=123"


msg="Generating test case '$(ansi -n --green "$TEST_CASE_NAME")' @ '$(ansi -n --cyan "$TEST_CASE_DIR")' using \n\t$(ansi -n --magenta "$TEMPLATE_MESON_BUILD, $TEMPLATE_H, $TEMPLATE_C")\nWith Commands\n\t'$(ansi -n --red "$J2_CMDS")'"

echo -e "$msg"
bash -xec "$J2_CMDS"
