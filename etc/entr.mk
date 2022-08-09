entr-files:
	@find . -type f -name "*.c" -or -name "*.h" -or -name "meson.build" -or -name "Makefile" -or -name "*.mk" -maxdepth 2
entr-run-cmd:
	@echo make build
entr-cmd:
	@echo "make entr-files|entr -c env bash -c \"$(shell make entr-run-cmd)\""
entr:
	@eval $(shell make entr-cmd)
