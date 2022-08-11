ENTRY_MAKE_ARGS=build
ENTR_CMD=make entr-files|entr -c make $(ENTRY_MAKE_ARGS)

_entr-files:
	@find . -type f -name "*.c" -or -name "*.h" -or -name "meson.build" -or -name "Makefile" -or -name "*.mk" -maxdepth 3
	@find ~/repos/c_vt100utils -type f -name "*.c" -or -name "*.h"

entr-files:
	@make _entr-files|xargs -I % realpath % |egrep -v '/submodules/'| $(SORT) -u

entr:
	@$(ENTR_CMD)
