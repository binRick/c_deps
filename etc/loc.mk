meson-binaries-loc:
	@make meson-binaries|xargs -I % echo %.c|$(SORT) -u|xargs Loc --files|bline -a bold:green -r yellow -R 1-6

