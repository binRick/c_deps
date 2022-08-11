default: all
##############################################################
include submodules/c_deps/etc/tools.mk
TESTS_LIST_LOG_FILE = $(shell pwd)/.tests-list.log
TESTS_SUITES_LOG_FILE=$(shell pwd)/.tests-suites.log
TESTS_TESTS_LOG_FILE=$(shell pwd)/.tests-tests.log
IGNORED_GO_H_FILES=$(shell ls "*/*.go"|gsed  's/\\.go$/\\.h/g' | xargs -I % echo -ne "-i % ")
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
TRIGGER_FILE=.trigger.c
include submodules/c_deps/etc/includes.mk
test-file-names:
	@grep greatest.h *-test/*-test.*|cut -d':' -f1|sort -u|xargs -I % basename %|cut -d'.' -f1


binaries-meson-link-bin:
	[[ -d .bin ]] || mkdir .bin
	make meson-binaries| cut -d'/' -f2-100 | xargs -I % echo -e "ln -s build/% $$(pwd)/.bin/$$(shell basename %)"
	#$$(pwd)/.bin/$$(basename $$f)\
#		env bash -c "ln -s $$(pwd)/$$f $$(pwd)/.bin/\$\$(basename $$f)" \
#		done
#|grep \..$|cut -d. -f1|sort -u


##############################################################
#suites:
#	@find ./build/*-test/*-test -type f | 
do-setup:
	@[[ -d submodules ]] || mkdir submodules
setup-binaries:
	@mkdir -p ~/.bin
	@command -v passh || { cd submodules/passh/. && make && cp passh ~/.bin/.; }
	@command -v gtimeout || brew install coreutils
setup-golang:
	@command -v goimports || go install golang.org/x/tools/cmd/goimports@latest
setup-wg:
	@command -v wg || brew install wireguard-tools
clone-repos:
	@ls $(shell echo ~/repos/debug_print_h)/.git || git clone ssh://git@github.com/binRick/debug_print_h $(shell echo ~/repos/debug_print_h)
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
install: do-install


do-install: all
	@meson install -C build
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
do-sync:
	rsync -arv ~/repos/c_deps \
		~/repos/c_ansi/submodules/. \
		--exclude="*/.git/*" \
		--exclude=".git/*" \
		--exclude '.git'
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
git-submodules-pull:
	@git submodule foreach git pull origin master --jobs=10
git-submodules-update:
	@git submodule update --init
git-pull:
	@git pull --recurse-submodules
do-uncrustify: uncrustify uncrustify-clean fix-dbg
ansi: all do-sync do-ansi-make
tidy: fmt-scripts do-uncrustify 
dev: do-nodemon
all: do-setup do-build do-test muon
trigger:
	@[[ -f $(TRIGGER_FILE) ]] && unlink $(TRIGGER_FILE)
	@touch $(TRIGGER_FILE)
do-pull-submodules-cmds:
	command find submodules -type d -maxdepth 1|xargs -I % echo -e "sh -c 'cd % && git pull'"
meson-ls-meson-build-files:
	@make meson-ls-buildsystem-files|grep "/meson.build$$"|sort -u

meson-ls-buildsystem-files:
	@meson introspect -a --buildsystem-files build -i| jq '.buildsystem_files' -M|grep '"'|cut -d'"' -f2|sort -u
bashful-pre:
	@ansi --save-palette
	@kfc -p vscode
	@ansi --hide-cursor
	@clear

bashful-post:
	@ansi -n --show-cursor

bashful: bashful-pre do-bashful bashful-post
bashful-clean: bashful-pre do-bashful-clean bashful-post
bashful-tidy: bashful-pre do-bashful-tidy bashful-post
bashful-build: bashful-pre do-bashful-build bashful-post
bashful-muon-build: bashful-pre do-bashful-muon-build bashful-post
bashful-git-status: bashful-pre bashful-rm-git-status-logs do-bashful-git-status bashful-post bashful-bat-git-status-logs
bashful-modified-files: bashful-pre bashful-rm-modified-files-logs do-bashful-modified-files bashful-post bashful-bat-modified-files-logs
bashful-git-diff: bashful-pre do-bashful-git-diff bashful-post
bashful-build-commands: bashful-pre do-bashful-build-commands bashful-post
bashful-test-commands: bashful-pre do-bashful-test-commands bashful-post
bashful-test: bashful-pre do-bashful-test bashful-post
bashful-view-git-diff: bashful-pre do-bashful-view-git-diff bashful-post
bashful-view-git-status: bashful-pre do-bashful-view-git-status bashful-post
bashful-view-modified-files: bashful-pre do-bashful-view-modified-files bashful-post


bashful-bat-modified-files-logs:
	@bat /tmp/meson-repos-modified-files-*.log 2>/dev/null||true
bashful-rm-modified-files-logs:
	@rm /tmp/meson-repos-modified-files-*.log 2>/dev/null||true

bashful-bat-git-status-logs:
	@bat /tmp/meson-repos-git-status-*.log 2>/dev/null||true
bashful-rm-git-status-logs:
	@rm /tmp/meson-repos-git-status-*.log 2>/dev/null||true

do-bashful-clean:
	@passh -L /tmp/meson-repos-do-clean.log bashful run --tags clean etc/meson-repos.yaml
do-bashful-tidy:
	@passh -L /tmp/meson-repos-do-tidy.log bashful run --tags tidy etc/meson-repos.yaml
do-bashful-muon-build:
	@passh -L /tmp/meson-repos-do-build.log bashful run --tags build etc/muon-repos.yaml
do-bashful-build:
	@passh -L /tmp/meson-repos-do-build.log bashful run --tags build etc/meson-repos.yaml
do-bashful-build-commands:
	@passh -L /tmp/meson-repos-do-build-commands.log bashful run --tags build-commands etc/meson-repos-info.yaml
do-bashful-test-commands:
	@passh -L /tmp/meson-repos-do-test-commands.log bashful run --tags test-commands etc/meson-repos-info.yaml
do-bashful-test:
	@passh -L /tmp/meson-repos-do-test.log bashful run --tags test etc/meson-repos.yaml
do-bashful-modified-files:
	@passh -L /tmp/meson-repos-do-modified-files.log bashful run --tags modified-files etc/meson-repos-info.yaml
do-bashful-git-status:
	@passh -L /tmp/meson-repos-do-git-status.log bashful run --tags git-status etc/meson-repos-info.yaml
do-bashful-git-diff:
	@passh -L /tmp/meson-repos-do-git-diff.log bashful run --tags git-diff etc/meson-repos-info.yaml
	@make do-bashful-view-git-diff


do-bashful-view-git-diff:
	@passh bat --style=full /tmp/meson-repos-git-diff-*.log
do-bashful-view-modified-files:
	@passh bat --style=full /tmp/meson-repos-modified-files-*.log
do-bashful-view-git-status:
	@passh bat --style=full /tmp/meson-repos-git-status-*.log

do-bashful:
	@passh -L /tmp/meson-repos-do-bashful-info.log bashful run etc/meson-repos-info.yaml
	@passh -L /tmp/meson-repos-do-bashful.log bashful run etc/meson-repos.yaml

meson-get-source-files:
	@meson introspect build --targets|jq '.[].target_sources[0].sources' -Mrc|cut -d'"' -f2|sort -u|gsed  "s|$(shell pwd)/||g"
	

