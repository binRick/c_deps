ENTR_MAKE_MODE=build
ENTR_RAW_CMD_ARGS=-r -c -s
###########################################
###       Example Override:
###  env MODE=meson-build CMD=./build/blocks-test/blocks-test make entr
###########################################
CMD ?= sleep 0
MODE ?= $(ENTR_MAKE_MODE)
WATCH ?= $(MAKE) entr-files
###########################################
ENTR_RAW_CMD=env SHELL=bash entr $(ENTR_RAW_CMD_ARGS) '$(MAKE) $(MODE) && $(CMD)'
ENTR_CMD=env bash +e -xc "while :; do $(ENTR_RAW_CMD) < <($(WATCH)); sleep 1; done"
###########################################
ENTR_FIND_MAX_DEPTH=3
ENTR_FIND_DIRS = . \
									 ~/repos/c_vt100utils
ENTR_FIND_NAMES = \
									"*.mk" \
									"Makefile" \
									"meson.build" \
									"*.c" \
									"*.h"
empty:=
space:= $(empty) $(empty)
ENTR_FIND_NAMES_SWITCHED := -name $(subst $(space), -or -name ,$(ENTR_FIND_NAMES))
b: 
	echo $(ENTR_FIND_NAMES_SWITCHED)
###########################################


_entr-files:
	@$(FIND) $(ENTR_FIND_DIRS) -type f \
		-not -path \*/.attic/\* \
		-and -not -path ./subprojects/\* \
		-and -not -path ./submodules/\* \
		-and -not -path ./build/\* \
		-and -not -path ./build-muon/\* \
		-and \( $(ENTR_FIND_NAMES_SWITCHED) \) \
		-maxdepth $(ENTR_FIND_MAX_DEPTH)

entr-files:
	@$(MAKE) _entr-files|$(XARGS) -I % $(REALPATH) % | $(SORT) -u

entr:
	@$(ENTR_CMD)
