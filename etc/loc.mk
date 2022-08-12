meson-binaries-loc:
	@$(MAKE) meson-binaries|$(XARGS) -I % echo %.c|$(SORT) -u|$(XARGS) Loc --files|$(BLINE) -a bold:green -r yellow -R 1-6

