meson-introspect-all:
	@meson introspect --all -i meson.build
meson-introspect-targets:
	@meson introspect --targets -i meson.build
meson-binaries:
	@meson introspect --targets build -i | jq 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc|grep submodules -v|xargs -I % basename %|$(SORT) -u
meson-binaries-paths:
	@make meson-binaries | xargs -I % echo ./build/%/%
meson-introspect-build-files:
	@meson introspect --buildsystem-files build |jq -rM|grep '"'|cut -d'"' -f2|$(SORT) -u|gsed "s|$(shell pwd)/||g"|$(SORT) -u
meson-get-source-files:
	@meson introspect build --targets|jq '.[].target_sources[0].sources' -Mrc|cut -d'"' -f2|sort -u|gsed  "s|$(shell pwd)/||g"
