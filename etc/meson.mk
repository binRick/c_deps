MESON_BUILD_DIR=build
MESON_PARALLEL_JOBS=20
######################################################################################################################################
meson-setup:
	@[[ -d $(MESON_BUILD_DIR) ]] && $(MESON) setup $(MESON_BUILD_DIR) --reconfigure || $(MESON) setup $(MESON_BUILD_DIR)

meson-build: meson-setup
	@$(MESON) compile -C $(MESON_BUILD_DIR) -j $(MESON_PARALLEL_JOBS)

do-build: meson-build muon-build

meson-install: do-meson
	@$(MESON) install -C $(MESON_BUILD_DIR) --tags build

install: meson-install

meson-test-verbose:
	@$(PASSH) $(MESON) test -C $(MESON_BUILD_DIR) --print-errorlogs -v
meson-test:
	@$(PASSH) $(MESON) test -C $(MESON_BUILD_DIR) --print-errorlogs	
test: meson-test muon-test
test-verbose: meson-test-verbose

do-meson: meson-build
meson: do-meson

build: meson muon

all: build test
