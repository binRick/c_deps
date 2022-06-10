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
DIR=$(shell $(PWD))	
##############################################################
TIDIED_FILES = deps*/*.c deps*/*.h
##############################################################
do-setup:
	@[[ -d submodules ]] || mkdir submodules


all: tidy
	@echo ALL

git-add:
	@git add meson/deps/*/meson.build
	@git add subprojects/*.wrap
	@git add deps*/*.c deps*/*.h
	@git status

fmt-scripts:
	@shfmt -w scripts/*.sh

do-uncrustify: uncrustify uncrustify-clean fix-dbg
uncrustify:
	@$(UNCRUSTIFY) -c etc/uncrustify.cfg --replace $(TIDIED_FILES)

uncrustify-clean:
	@find  . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)

do-build: do-meson do-ninja

do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }

do-ninja:
	@eval cd . && { ninja -C build; }

do-ninja-test:
	@eval cd . && { ninja test -C build -v; }

do-test: do-ninja-test

build: do-meson do-build

do-sync:
	rsync -arv ~/repos/meson_deps \
		~/repos/c_ansi/submodules/. \
		--exclude="*/submodules/*" --exclude="*/.git/*" --exclude '.git/' --exclude 'submodules/'

do-ansi-make:
	@cd ~/repos/c_ansi && make

ansi: all do-sync do-ansi-make

tidy: \
	do-setup \
	fmt-scripts do-uncrustify \
	do-build \
	do-test \
	git-add
