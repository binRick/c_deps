default: all
##############################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
UNCRUSTIFY=$(shell command -v uncrustify)
PWD=$(shell command -v pwd)
FIND=$(shell command -v find)
EMBED_BINARY=$(shell command -v embed)
JQ_BIN=$(shell command -v jq)
DIR=$(shell pwd)	
TESTS_LIST_LOG_FILE = $(shell pwd)/.tests-list.log
TESTS_SUITES_LOG_FILE=$(shell pwd)/.tests-suites.log
TESTS_TESTS_LOG_FILE=$(shell pwd)/.tests-tests.log
IGNORED_GO_H_FILES=$(shell ls "*/*.go"|gsed  's/\\.go$/\\.h/g' | xargs -I % echo -ne "-i % ")
##############################################################
TIDIED_FILES = deps*/*.c deps*/*.h term*/*.c term*/*.h ctable*/*.c ctable*/*.h *table*/*.c *table*/*.h cgif-test/*.c *-test/*.c *-test/*.h chan-test/*.c chan-test/*.h \
			   introspect-test/*.c introspect-test/*.h \
			   introspect/*.c introspect/*.h \
			   reproc-test/*.c reproc-test/*.h \
			   list-test/*.c list-test/*.h \
			   *-test/*.c *-test/*.h \
			   intro*/*.c intro*/*.h 
########################################################
TRIGGER_FILE=.trigger.c
##############################################################
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
uncrustify:
	@$(UNCRUSTIFY) -c etc/uncrustify.cfg --replace $(TIDIED_FILES)||true
uncrustify-clean:
	@find  . -type f -maxdepth 2 -name "*unc-back*"|xargs -I % unlink %
clean: rm-make-logs
	@rm -rf build .cache
fix-dbg:
	@$(SED) 's|, % c);|, %c);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % u);|, %u);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)
install: do-install


do-muon-setup:
	@muon setup build-muon

do-muon-clean:
	@rm -rf build-muon

do-muon-build:
	@muon samu -C build-muon

do-muon-install:
	@cd build-muon && muon install


do-muon-test:
	@cd build-muon && muon test


build-muon: do-muon-setup do-muon-build do-muon-test

do-install: all
	@meson install -C build
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }
do-sync:
	rsync -arv ~/repos/meson_deps \
		~/repos/c_ansi/submodules/. \
		--exclude="*/.git/*" \
		--exclude=".git/*" \
		--exclude '.git'
do-nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) \
		--delay .3 \
		-w "dbgp-test/*.h" -w "dbgp-test/*.c"\
		-w 'meson/meson.build' -w 'meson/deps/*/meson.build' -w 'meson.build' \
		-w Makefile \
		-i '*/embeds/*' -i 'subprojects/*/' -i submodules -i 'build/*' \
		-w "term-tests" \
		-w "chan-test/*.c" -w "chan-test/*.h" \
		-w "reproc-test/*.c" -w "reproc-test/*.h" \
		-w "*-test/*.c" -w "*-test/*.h" \
		-w "*/*.c" -w "*/*.h" \
	    -w "introspect-test/*.c" -w "introspect-test/*.h" \
	    -w "introspect/*.c" -w "introspect/*.h" \
		-w "term-tests-test" \
		-i confirm1/confirm1.h -i flinch/new.h -i multi_select/multi_select.h -i multi_select0/multi_select0.h -i multi_select1/multi_select1.h -i select_description1/select_description1.h \
		-i build \
			-e Makefile,tpl,build,sh,c,h,Makefile \
			-x env -- bash -c 'make||true'
git-submodules-pull:
	@git submodule foreach git pull origin master --jobs=10
git-submodules-update:
	@git submodule update --init
git-pull:
	@git pull --recurse-submodules
do-uncrustify: uncrustify uncrustify-clean fix-dbg
do-build: do-meson
	@meson compile -C build
	@meson install -C build --tags build
do-test:
	@passh meson test -C build -v --print-errorlogs	
test: do-test
build: do-meson do-build
ansi: all do-sync do-ansi-make
tidy: fmt-scripts do-uncrustify 
dev: do-nodemon
all: do-setup do-build do-test
trigger:
	@[[ -f $(TRIGGER_FILE) ]] && unlink $(TRIGGER_FILE)
	@touch $(TRIGGER_FILE)
meson-introspect-all:
	@meson introspect --all -i meson.build
meson-introspect-targets:
	@meson introspect --targets -i meson.build
meson-binaries:
	@meson introspect --targets  meson.build -i | jq 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc|xargs -I % echo build/%
meson-binaries-loc:
	@make meson-binaries|xargs -I % echo %.c|sort -u|xargs Loc --files|bline -a bold:green -r yellow -R 1-6

do-pull-submodules-cmds:
	command find submodules -type d -maxdepth 1|xargs -I % echo -e "sh -c 'cd % && git pull'"

run-binary:
	@make meson-binaries | fzf --reverse | xargs -I % sh -xc "./%" 
meson-tests-list:
	@meson test -C build --list
meson-tests:
	@make meson-tests-list|fzf --reverse -m | xargs -I % env cmd="\
		meson test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs \"%\"" \
			env bash -c '\
	passh "$$cmd" && \
	ansi -n --green --bold "OK" && \
	echo -n "> " && \
	ansi -n --yellow --italic "$$cmd" && \
	echo \
'	

bashful-pre:
	@ansi --save-palette
	@kfc -s vscode
	@ansi --hide-cursor
	@clear

bashful-post:
	@ansi --load-palette
	@ansi --show-cursor

bashful: bashful-pre do-bashful bashful-post
bashful-clean: bashful-pre do-bashful-clean bashful-post
bashful-tidy: bashful-pre do-bashful-tidy bashful-post
bashful-build: bashful-pre do-bashful-build bashful-post
bashful-muon-build: bashful-pre do-bashful-muon-build bashful-post
bashful-git-status: bashful-pre do-bashful-git-status bashful-post
bashful-git-diff: bashful-pre do-bashful-git-diff bashful-post
bashful-build-commands: bashful-pre do-bashful-build-commands bashful-post
bashful-test-commands: bashful-pre do-bashful-test-commands bashful-post
bashful-test: bashful-pre do-bashful-test bashful-post
bashful-view-git-diff: bashful-pre do-bashful-view-git-diff bashful-post
bashful-view-git-status: bashful-pre do-bashful-view-git-status bashful-post


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
do-bashful-git-status:
	@passh -L /tmp/meson-repos-do-git-status.log bashful run --tags git-status etc/meson-repos-info.yaml
do-bashful-git-diff:
	@passh -L /tmp/meson-repos-do-git-diff.log bashful run --tags git-diff etc/meson-repos.yaml


do-bashful-view-git-diff:
	@passh bat --style=full /tmp/meson-repos-git-diff-*.log
do-bashful-view-git-status:
	@passh bat --style=full /tmp/meson-repos-git-status-*.log

do-bashful:
	@passh -L /tmp/meson-repos-do-bashful-info.log bashful run etc/meson-repos-info.yaml
	@passh -L /tmp/meson-repos-do-bashful.log bashful run etc/meson-repos.yaml



