ENTRY_MAKE_ARGS=build
ENTR_CMD=$(MAKE) entr-files|entr -c $(MAKE) $(ENTRY_MAKE_ARGS)

_entr-files:
	@$(FIND) . -type f -name "*.c" -or -name "*.h" -or -name "meson.build" -or -name "Makefile" -or -name "*.mk" -maxdepth 3
	@$(FIND) ~/repos/c_vt100utils -type f -name "*.c" -or -name "*.h"

entr-files:
	@$(MAKE) _entr-files|$(XARGS) -I % $(REALPATH) % |$(GREP) -v '/submodules/'| $(SORT) -u

entr:
	@$(ENTR_CMD)
