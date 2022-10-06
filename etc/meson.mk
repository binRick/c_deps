MESON_BUILD_DIR=build
MESON_DEFAULT_BUILD_TYPE=release
MESON_DEFAULT_BUILD_TYPE=minsize
MESON_DEFAULT_BUILD_TYPE=debug
BUILD_TYPE ?=$(MESON_DEFAULT_BUILD_TYPE)
BUILD_JOBS ?=15
TEST_JOBS ?=3
MESON_DEFAULT_LIBRARY ?=shared
BUILD_OPTIMIZATION ?=0
WARN_LEVEL ?=1
MESON_PARALLEL_JOBS=$(BUILD_JOBS)
MESON_BUILD_TYPE=$(BUILD_TYPE)
MESON_BUILD_LOG=$(MESON_BUILD_DIR)/build.log
MESON_SETUP_ARGS=--fatal-meson-warnings --buildtype $(MESON_BUILD_TYPE) --default-library $(MESON_DEFAULT_LIBRARY) --warnlevel $(WARN_LEVEL) --backend ninja --errorlogs
meson-setup:
	@if [[ -d $(MESON_BUILD_DIR) ]]; then $(MESON) setup $(MESON_SETUP_ARGS) --reconfigure $(MESON_BUILD_DIR); else $(MESON) setup $(MESON_SETUP_ARGS) $(MESON_BUILD_DIR); fi
meson-build: meson-setup
	@$(PASSH) -L $(MESON_BUILD_LOG) $(MESON) compile -C $(MESON_BUILD_DIR) -j $(MESON_PARALLEL_JOBS)
do-build: meson-build
scan-build:
	@env SCANBUILD=$(SCAN_BUILD) ninja -C $(MESON_BUILD_DIR) scan-build
meson-install: do-meson
	@$(MESON) install -C $(MESON_BUILD_DIR)
install: meson-install
meson-test-verbose:
	@env MESON_TESTTHREADS=$(TEST_JOBS) $(PASSH) $(MESON) test -C $(MESON_BUILD_DIR) --print-errorlogs -v
meson-test:
	@env MESON_TESTTHREADS=$(TEST_JOBS) $(PASSH) $(MESON) test -C $(MESON_BUILD_DIR) --print-errorlogs	
test: meson-test 
test-verbose: meson-test-verbose
do-meson: do-build
meson: do-meson
build: meson 
all: build test
warning-report:
	@$(GREP) warning: $(MESON_BUILD_LOG)|egrep -v '/submodules/'|cut -d':' -f1|sort |uniq -c|sort -n
