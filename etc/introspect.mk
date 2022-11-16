meson-introspect-all:
	@$(MESON) introspect --all -i meson.build
meson-introspect-targets:
	@$(MESON) introspect --targets -i meson.build
meson-binaries:
	@$(MESON) introspect --targets build -i | $(JQ) 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc|grep submodules -v|$(XARGS) -I % $(BASENAME) %|$(SORT) -u
meson-binaries-paths:
	@$(MAKE) -s meson-binaries | $(XARGS) -I % echo ./build/%/%
meson-introspect-build-files:
	@$(MESON) introspect --buildsystem-files build |$(JQ) -rM|grep '"'|$(CUT) -d'"' -f2|$(SORT) -u|$(SED) "s|$(shell pwd)/||g"|$(SORT) -u
meson-get-source-files:
	@$(MESON) introspect build --targets|$(JQ) '.[].target_sources[0].sources' -Mrc|$(CUT) -d'"' -f2|$(SORT) -u|$(SED)  "s|$(shell pwd)/||g"

meson-get-source-dirs:
	@$(MAKE) -s meson-introspect-build-files -B \
			|egrep 'submodules|subprojects|meson/deps' -v|grep 'meson.build'\
			|gsed 's|/meson.build$$||g'|grep '^[a-z].*'|sort -u\
			|tr '\n' ' '

meson-get-c-files:
	@$(FIND) $(shell $(MAKE) -s meson-get-source-dirs) -type f -name "*.c" -or -name "*.h"|sort -u|egrep -v '/\.'|$(GREP) -v 'meson/deps|submodules|subprojects'|$(GREP) '\.c$$|\.h$$'|$(SORT) -u
