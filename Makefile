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
##############################################################
TIDIED_FILES = deps*/*.c deps*/*.h term*/*.c term*/*.h ctable*/*.c ctable*/*.h *table*/*.c *table*/*.h gumbo-test/*.c gumbo-test/*.h cgif-test/*.c *-test/*.c *-test/*.h chan-test/*.c chan-test/*.h \
			   introspect-test/*.c introspect-test/*.h \
			   introspect/*.c introspect/*.h \
			   reproc-test/*.c reproc-test/*.h \
			   list-test/*.c list-test/*.h \
			   *-test/*.c *-test/*.h \
########################################################
TRIGGER_FILE=.trigger.c
##############################################################
do-setup:
	@[[ -d submodules ]] || mkdir submodules
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

clean:
	@rm -rf build .cache

fix-dbg:
	@$(SED) 's|, % c);|, %c);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % u);|, %u);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)
do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; echo MESON OK; }
do-ninja:
	@eval cd . && { ninja -C build; echo NINJA OK; }
do-ninja-test:
	@eval cd . && { passh ninja test -C build -v; echo NINJA TEST OK; }
do-deps-test:
	@passh ./build/deps-test/deps-test -v
do-sync:
	rsync -arv ~/repos/meson_deps \
		~/repos/c_ansi/submodules/. \
		--exclude="*/submodules/*" --exclude="*/.git/*" --exclude '.git/' --exclude 'submodules/'
do-ansi-make:
	@cd ~/repos/c_ansi && make
unlink-term-tests-test:
	@unlink build/term-tests-test/term-tests-test||true
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
	    -w "introspect-test/*.c" -w "introspect-test/*.h" \
	    -w "introspect/*.c" -w "introspect/*.h" \
		-w "term-tests-test" \
			-e Makefile,tpl,build,sh,c,h,Makefile \
			-x env -- bash -xc 'make'

tests-log:
	@rm .test*.log 2>/dev/null||true
	@./build/deps-test/deps-test -l | tee $(TESTS_LIST_LOG_FILE) >/dev/null

tests-tests: tests-log
	@grep -v "^* Suite .*:" $(TESTS_LIST_LOG_FILE)\
		|cut -d: -f1|cut -d ' ' -f3|sort -u | tee $(TESTS_TESTS_LOG_FILE) >/dev/null

tests-suite-tests: tests-tests tests-suites
tests-clean:
	@rm .test*.log

tests-suites:
	@grep "^* Suite .*:" $(TESTS_LIST_LOG_FILE)\
		|cut -d: -f1|cut -d ' ' -f3\
		|sort -u \
		|tee $(TESTS_SUITES_LOG_FILE) >/dev/null

tests: do-encode-tests
do-encode-tests: do-build do-tests tests-clean
do-tests: tests-log tests-suite-tests tests-suites 
	@rm .tests.json 2>/dev/null||true
	@./scripts/tests-encoder.sh > .tests.json && clear && jq -c < .tests.json

git-submodules-pull:
	@git submodule foreach git pull origin master --jobs=10

git-submodules-update:
	@git submodule update --init
#	--recursive

git-pull:
	@git pull --recurse-submodules

do-uncrustify: uncrustify uncrustify-clean fix-dbg
do-build: do-meson do-ninja
do-test: do-ninja-test do-deps-test
test: do-test
build: do-meson do-build
ansi: all do-sync do-ansi-make
tidy: \
	do-setup \
	fmt-scripts do-uncrustify \
	do-build \
	git-add
dev: do-nodemon
all: do-setup do-build trigger
trigger:
	@[[ -f $(TRIGGER_FILE) ]] && unlink $(TRIGGER_FILE)
	@touch $(TRIGGER_FILE)
meson-introspect-targets:
	@meson introspect --targets -i meson.build

meson-binaries:
	@meson introspect --targets  meson.build -i | jq 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc
