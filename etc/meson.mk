############################################
MESON_BUILD_DIR=build
MESON_DEFAULT_BUILD_TYPE=minsize
MESON_DEFAULT_BUILD_TYPE=debug
############################################
BUILD_TYPE ?=$(MESON_DEFAULT_BUILD_TYPE)
BUILD_JOBS ?=10
TEST_JOBS ?=10
MESON_DEFAULT_LIBRARY ?=static
WARN_LEVEL ?=2
############################################
MESON_PARALLEL_JOBS=$(BUILD_JOBS)
MESON_BUILD_TYPE=$(BUILD_TYPE)

MESON_SETUP_ARGS=\
								 --buildtype $(MESON_BUILD_TYPE) \
								 --strip \
								 --default-library $(MESON_DEFAULT_LIBRARY) \
								 --prefer-static \
								 --warnlevel $(WARN_LEVEL) \
								 --backend ninja \
								 --errorlogs

meson-setup:
	@[[ -d $(MESON_BUILD_DIR) ]] && $(MESON) setup $(MESON_SETUP_ARGS) --reconfigure $(MESON_BUILD_DIR) || $(MESON) setup $(MESON_SETUP_ARGS) $(MESON_BUILD_DIR)

meson-build: meson-setup
	@$(MESON) compile -C $(MESON_BUILD_DIR) -j $(MESON_PARALLEL_JOBS)
	#| tee .meson-build.log
	#@$(GREP) 'warning:' .meson-build.log |egrep -v 'submodules|unused parameter' | tee .meson-build-warnings.log

do-build: meson-build muon-build

scan-build:
	@env SCANBUILD=$(SCAN_BUILD) ninja -C $(MESON_BUILD_DIR) scan-build

meson-install: do-meson
	@$(MESON) install -C $(MESON_BUILD_DIR)

install: meson-install

meson-test-verbose:
	@env MESON_TESTTHREADS=$(TEST_JOBS) $(PASSH) $(MESON) test -C $(MESON_BUILD_DIR) --print-errorlogs -v
meson-test:
	@env MESON_TESTTHREADS=$(TEST_JOBS) $(PASSH) $(MESON) test -C $(MESON_BUILD_DIR) --print-errorlogs	
test: meson-test muon-test
test-verbose: meson-test-verbose

do-meson: meson-build
meson: do-meson

build: meson muon

all: build test
