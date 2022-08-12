
git-add:
	@$(GIT) add meson/deps/*/meson.build
	@$(GIT) add subprojects/*.wrap
	@$(GIT) add deps*/*.c deps*/*.h
	@$(GIT) add scripts/*.sh
	@$(GIT) status --ignore-submodules
git-submodules-pull:
	@$(GIT) submodule foreach git pull origin master --jobs=10
git-submodules-update:
	@$(GIT) submodule update --init
git-pull:
	@$(GIT) pull --recurse-submodules
do-pull-submodules-cmds:
	@$(FIND) submodules -type d -maxdepth 1|$(XARGS) -I % echo -e "sh -c 'cd % && $(GIT) pull'"
clone-repos:
	@$(LS) $(shell echo ~/repos/debug_print_h)/.git || $(GIT) clone ssh://git@github.com/binRick/debug_print_h $(shell echo ~/repos/debug_print_h)
