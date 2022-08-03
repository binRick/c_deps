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
			   intro*/*.c intro*/*.h \
			   exec-fzf*/*.c exec-fzf*/*.h 
########################################################
TRIGGER_FILE=.trigger.c
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
greatest-suites:
	@(make test-file-names | while read -r f; do timeout .5 passh ./build/$$f/$$f -l -v; done) |grep '^* Suite '|cut -d: -f1|cut -d' ' -f3
greatest-suite-tests:
	@passh  ./build/exec-fzf-test/exec-fzf-test -l -v -s s_fzf_basic|grep '^* Suite ' -A 999|grep '^[[:space:]]'|tr -d ' '|cut -d' ' -f1

do-muon-setup:
	@muon setup build-muon

do-muon-clean:
	@rm -rf build-muon

do-muon-build:
	@muon samu -C build-muon -j 20 -k 1

do-muon-install:
	@cd build-muon && muon install
do-muon-test:
	@cd build-muon && muon -C build-muon test -w 20 -f
build-muon: do-muon-setup do-muon-build
do-muon: build-muon
muon: do-muon

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
clean: rm-make-logs do-muon-clean
	@rm -rf build .cache
fix-dbg:
	@$(SED) 's|, % c);|, %c);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % u);|, %u);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)
install: do-install


do-install: all
	@meson install -C build
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }
do-sync:
	rsync -arv ~/repos/c_deps \
		~/repos/c_ansi/submodules/. \
		--exclude="*/.git/*" \
		--exclude=".git/*" \
		--exclude '.git'
do-nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) \
		-V \
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
meson: do-meson-build
do-build: do-meson-build
meson-build: do-meson-build
do-meson-build: do-meson
	@meson compile -C build -j 20 -v
do-meson-install: do-meson
	@meson install -C build --tags build
do-test:
	@passh meson test -C build -v --print-errorlogs	
muon: do-muon
test: do-test
build: do-meson do-build
ansi: all do-sync do-ansi-make
tidy: fmt-scripts do-uncrustify 
dev: do-nodemon
all: do-setup do-build do-test muon
trigger:
	@[[ -f $(TRIGGER_FILE) ]] && unlink $(TRIGGER_FILE)
	@touch $(TRIGGER_FILE)
meson-introspect-all:
	@meson introspect --all -i meson.build
meson-introspect-targets:
	@meson introspect --targets -i meson.build
meson-binaries:
	@meson introspect --targets   build -i | jq 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc
#	#@meson introspect --targets  meson.build -i | jq 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc|xargs -I % echo build/%
meson-binaries-loc:
	@make meson-binaries|xargs -I % echo %.c|sort -u|xargs Loc --files|bline -a bold:green -r yellow -R 1-6
deps-test-ls-tests:
	@eval build/deps-test/deps-test -l
deps-test-ls-suites:
	@eval build/deps-test/deps-test -L
do-pull-submodules-cmds:
	command find submodules -type d -maxdepth 1|xargs -I % echo -e "sh -c 'cd % && git pull'"
run-binary1:
	@make meson-binaries | fzf --reverse | xargs -I % sh -xc "./%" 
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
	@passh -L /tmp/meson-repos-do-git-diff.log bashful run --tags git-diff etc/meson-repos.yaml


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
run-binary:
	@clear; make meson-binaries | env FZF_DEFAULT_COMMAND= \
        fzf --reverse \
            --preview-window='follow,wrap,right,80%' \
            --bind 'ctrl-b:preview(make meson-build)' \
            --preview='env bash -c {} -v -a' \
            --ansi --border \
            --cycle \
            --header='Select Test Binary' \
            --height='100%' \
    | xargs -I % env bash -c "./%"
run-binary-nodemon:
	@make meson-binaries | fzf --reverse | xargs -I % nodemon -w build --delay 1000 -x passh "./%"
meson-tests-list:
	@meson test -C build --list
	
meson-tests-preview-header:
	@printf "%s\n"   " $(shell ansi --green --bold "Keybinds") "
	@printf "         |-------------------------------|"
	@printf "\n"
	@printf "         | - %s           |\n"    "$(shell ansi --yellow "control+p:sources")"
	@printf "         | - %s           |\n"    "$(shell ansi --red "control+b:rebuild")"
	@printf "         | - %s             |\n" "$(shell ansi --magenta --italic "control+k:clean")"
	@printf "         | - %s             |\n" "$(shell ansi --yellow-intense --italic "control+t:tests")"
	@printf "         | - %s  |" "$(shell ansi --green-intense "control+/,control+l:hwidth")"
	@printf "\n"
	@printf "         |"
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "Layout") "
	@printf "\n"
	@printf "                 - Adjust Vertical Layout      :   %s" "$(shell ansi --red-intense "control+/   control+n")"
	@printf "\n"
	@printf "                 - Adjust Horizontal Layout    :   %s" "$(shell ansi --red-intense "control+n   control+m")"
	@printf "\n"
	@printf "                 - Meson Test Suites           :   %s" "$(shell ansi --cyan --italic "control+s")"
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "Source Code") "
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "Dependencies") "
	@printf "\n"
	@printf "         |  - %s           |" "$(shell ansi --green-intense "control+v:configured")"
	@printf "\n"
	@printf "         |  - %s         |" "$(shell ansi --magenta-intense "control+w:unconfigured")"
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "Build") "
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "GIT") "
	@printf "\n"
	@printf "         |  - %s   |" "$(shell ansi --green-intense "control+e:git status")"
	@printf "\n"
	@printf "         |  - %s         |" "$(shell ansi --magenta-intense "control+g:tidy")"
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "Dependencies") "
	@printf "\n"
	@printf "         |%s|"   " $(shell ansi --green --bold "deps-test") "
	@printf "\n"
	@printf "         |-------------------------------|"
	@printf "\n"

#	@printf "ctrl+s:suites|ctrl+t:tests|ctrl+b:rebuild|ctrl+k:clean|ctrl+l:width|ctrl+/:thin width|ctrl+y/u:scroll preview|ctrl+g:tidy|ctrl+e:git-status|ctrl+w:unconf deps|ctrl+v:conf deps|ctrl+i:make dev|ctrl+r:bashful build"
meson-tests:
	@\
	{ \
	make meson-tests-list; } \
  	  |fzf \
		--border=sharp\
		--margin=0,0,0,0 --padding=0,0,0,0 \
		--no-info \
        --reverse --ansi --no-multi --cycle --info=inline \
        --bind 'ctrl-w:preview(./meson/ls_unconfigured_submodules.sh)' \
        --bind 'ctrl-v:preview(./meson/ls_configured_submodules.sh)' \
        --bind 'ctrl-space:preview(make meson-tests-preview-header)'\
        --bind 'ctrl-e:preview(git status)' \
        --bind 'ctrl-g:preview(make tidy)' \
        --bind 'ctrl-b:preview(make meson-build)' \
		--bind 'ctrl-x:preview(passh muon info options)'\
		--bind 'ctrl-p:change-prompt(Source Files > )'\
			--bind 'ctrl-p:+change-preview(make bat --color always --italic-text always --decorations always --theme "Monokai Extended" {})'\
		    --bind 'ctrl-p:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
			--bind 'ctrl-p:+reload(make meson-get-source-files)'\
		--bind 'ctrl-o:change-prompt(Meson Tests > )'\
		    --bind 'ctrl-o:+change-preview(meson test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs {} || build/{}/{})' \
		    --bind 'ctrl-o:+change-preview-window(follow,nowrap)'\
			--bind 'ctrl-o:+reload(make meson-tests-list)' \
        --bind 'ctrl-k:preview(make clean meson-build)'\
		--bind 'ctrl-h:preview(passh build/deps-test/deps-test -v -e -a -t {} )'\
		--bind 'ctrl-j:preview(passh build/deps-test/deps-test -v -e -a -s {} )'\
		--bind 'ctrl-t:change-prompt(Tests -> ctrl+h to run > )'\
        	--bind 'ctrl-t:+change-preview(scripts/deps-test-view-test.sh {})'\
			--bind 'ctrl-t:+reload(make deps-test-ls-tests -B)'\
		    --bind 'ctrl-t:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
		--bind 'ctrl-s:+change-prompt(Suites -> ctrl+j to run > )'\
        	--bind 'ctrl-s:+change-preview(scripts/deps-test-view-suite.sh {})'\
     		--bind 'ctrl-s:+reload(make deps-test-ls-suites -B)'\
		    --bind 'ctrl-s:+change-preview-window(nofollow,nowrap,~5,+{2}+5/2)'\
        --bind 'ctrl-y:preview-half-page-up'\
        --bind 'ctrl-u:preview-half-page-down'\
        --bind 'ctrl-/:change-preview-window(right,80%|right,70%,border-horizontal)'\
        --bind 'ctrl-l:change-preview-window(right,60%|right,50%,border-horizontal)'\
        --bind 'ctrl-m:change-preview-window(down,80%|down,70%,border-vertical)' \
        --bind 'ctrl-n:change-preview-window(down,60%|down,50%,border-vertical)' \
        --bind 'ctrl-i:change-preview(scripts/deps-test-view-test.sh {})'\
        --preview='meson test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs {}' \
        --preview-window='follow,wrap,right,75%' \
        --header='Control Space For Menu'\
        --header-lines=0 \
        --height='100%'\



#meson-tests-preview-header:
#		mesonSelect Test Case |ctrl+p:sources|ctrl+s:suites|ctrl+t:tests|ctrl+b:rebuild|ctrl+k:clean|ctrl+l:width|ctrl+/:thin width|ctrl+y/u:scroll preview|ctrl+g:tidy|ctrl+e:git-status|ctrl+w:unconf deps|ctrl+v:conf deps|ctrl+i:make dev|ctrl+r:bashful build|'\
