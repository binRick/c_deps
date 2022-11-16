ENTR_MAKE_MODE=build
ENTR_RAW_CMD_ARGS=-r -c -s
###########################################
###       Example Override:
###  env MODE=meson-build CMD="./build/blocks-test/blocks-test -v -a " make entr
###########################################
CMD ?= sleep 0
MODE ?= $(ENTR_MAKE_MODE)
WATCH ?= $(MAKE) entr-files
###########################################
ENTR_RAW_CMD=env SHELL=/usr/local/bin/bash $(ENTR) $(ENTR_RAW_CMD_ARGS) '$(MAKE) -B $(MODE) && $(CMD)'
ENTR_CMD=env bash +e -xc "while :; do $(ENTR_RAW_CMD) < <($(WATCH)); sleep 1; done"
###########################################
ENTR_FIND_MAX_DEPTH=3
ENTR_FIND_DIRS = . submodules/meson.build \
									 ~/repos/c_deps/submodules/log \
									 ~/repos/c_ansi \
									 ~/repos/msf_gif \
									 ~/repos/c_darwin/httpserver-utils/.assets \
									 ~/repos/c_deps ~/repos/c_deps/meson/deps ~/repos/c_deps/etc \
									 ~/repos/c_darwin ~/repos/c_darwin/submodules/meson.build
ENTR_FIND_NAMES = \
									"*.mk" \
									"Makefile" \
									"meson.build" \
									"*.c" \
									"*.html" \
									"*.css" \
									"*.js" \
									"*.h" 
empty:=
space:= $(empty) $(empty)
ENTR_FIND_NAMES_SWITCHED := -name $(subst $(space), -or -name ,$(ENTR_FIND_NAMES))
###########################################
_entr-files:
	@$(FIND) $(ENTR_FIND_DIRS) \
		-maxdepth $(ENTR_FIND_MAX_DEPTH)\
		-type f \
		-not -path \*.attic\* \
		-and -not -path \*/subprojects/\* \
		-and -not -path \*/\.\* \
		-and -not -path \*/submodules/\* \
		-and -not -path \*/wrapdb/\* \
		-and -not -path \*/build/\* \
		-and -not -path \*/build-muon/\* \
		-and -not -path \*/gpp-\* \
		-name "*.c" -or -name "*.h" -or -name "*.j2" -or -name "*.gpp"
		2>/dev/null

entr-files:
	@$(MAKE) _entr-files|egrep -v '"'|xargs $(REALPATH)|  $(SORT) -u
entr:
	@$(ENTR_CMD)
