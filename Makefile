default: all
##############################################################
DIR=$(shell pwd)
ETC_DIR=$(DIR)/etc

##############################################################
TIDIED_FILES = deps*/*.c deps*/*.h term*/*.c term*/*.h ctable*/*.c ctable*/*.h *table*/*.c *table*/*.h cgif-test/*.c *-test/*.c *-test/*.h chan-test/*.c chan-test/*.h \
			   introspect-test/*.c introspect-test/*.h \
			   introspect/*.c introspect/*.h \
			   reproc-test/*.c reproc-test/*.h \
			   list-test/*.c list-test/*.h \
			   *-test/*.c *-test/*.h \
			   intro*/*.c intro*/*.h \
			   exec-fzf*/*.c exec-fzf*/*.h \
			   submodules/c_vt100utils/vt100utils.h \
			   submodules/c_vt100utils/demos/tuibox.h

########################################################
include submodules/c_deps/etc/includes.mk
test-file-names:
	@grep greatest.h *-test/*-test.*|cut -d':' -f1|sort -u|xargs -I % basename %|cut -d'.' -f1
binaries-meson-link-bin:
	[[ -d .bin ]] || mkdir .bin
	make meson-binaries| cut -d'/' -f2-100 | xargs -I % echo -e "ln -s build/% $$(pwd)/.bin/$$(shell basename %)"
setup-binaries:
	@mkdir -p ~/.bin
	@command -v passh || { cd submodules/passh/. && make && cp passh ~/.bin/.; }
	@command -v gtimeout || brew install coreutils
setup-golang:
	@command -v goimports || go install golang.org/x/tools/cmd/goimports@latest
setup-wg:
	@command -v wg || brew install wireguard-tools
link-repos:
	@ls submodules/c_ansi || ln -s $(shell echo ~/repos/c_ansi) submodules/c_ansi
	@ls submodules/debug_print_h/src || ln -s $(shell echo ~/repos/debug_print_h) submodules/debug_print_h
git-add:
	@git add meson/deps/*/meson.build
	@git add subprojects/*.wrap
	@git add deps*/*.c deps*/*.h
	@git add scripts/*.sh
	@git status
fmt-scripts:
	@shfmt -w scripts/*.sh
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
do-nodemon:
	@$(NODEMON) \
		-I \
		--delay .3 \
		-w "dbgp-test/*.h" -w "dbgp-test/*.c"\
		-w 'meson/meson.build' -w 'meson/deps/*/meson.build' -w 'meson.build' \
		-w Makefile \
		-w "term-tests" \
		-w "chan-test/*.c" -w "chan-test/*.h" \
		-w "reproc-test/*.c" -w "reproc-test/*.h" \
		-w "*-test/*.c" -w "*-test/*.h" \
		-w "*/*.c" -w "*/*.h" \
	    -w "introspect-test/*.c" -w "introspect-test/*.h" \
	    -w "introspect/*.c" -w "introspect/*.h" \
		-w "term-tests-test" \
		-i submodules -i meson-muon -i .cache -i subprojects \
		-i '*/embeds/*' -i 'subprojects/*/' -i submodules -i 'build/*' \
		-i confirm1/confirm1.h -i flinch/new.h -i multi_select/multi_select.h \
		-i multi_select0/multi_select0.h -i multi_select1/multi_select1.h \
		-i select_description1/select_description1.h \
		-i build \
		-i build-muon \
		-i .cache \
		-i .git \
		-i submodules \
			-e Makefile,tpl,build,sh,c,h,Makefile \
			-x env -- bash --norc --noprofile -c 'clear;make||true'
ansi: all do-sync do-ansi-make
dev: do-nodemon
all: meson muon test
meson-ls-meson-build-files:
	@make meson-ls-buildsystem-files|grep "/meson.build$$"|sort -u
meson-ls-buildsystem-files:
	@meson introspect -a --buildsystem-files build -i| jq '.buildsystem_files' -M|grep '"'|cut -d'"' -f2|sort -u
meson-get-source-files:
	@meson introspect build --targets|jq '.[].target_sources[0].sources' -Mrc|cut -d'"' -f2|sort -u|gsed  "s|$(shell pwd)/||g"
	

