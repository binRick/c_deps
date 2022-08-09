do-meson-build:
	@meson setup build || meson setup build --reconfigure
	@meson compile -C build -j 20 -v
meson-build: do-meson-build
do-meson-install: do-meson
	@meson install -C build --tags build

do-test:
	@meson test -C build -v --print-errorlogs
do-meson: meson-build
do-install: meson-install
do-meson-test:
	@passh meson test -C build -v --print-errorlogs	
meson-test: do-meson-test
test: meson-test muon-test
build: do-build
meson-build: do-meson-build
do-install: do-meson-install
install: do-install
do-build: meson-build muon-build
