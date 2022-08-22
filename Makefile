default: all
include submodules/c_deps/etc/includes.mk
local-setup: setup-binaries setup-golang setup-wg setup
##############################################################
TIDIED_FILES = */*.c */*.h \
			   submodules/c_vt100utils/vt100utils.h \
			   submodules/c_vt100utils/vt100utils.c \
			   submodules/c_vt100utils/tuibox.c \
			   submodules/c_vt100utils/tuibox.h \
			   submodules/c_vt100utils/tuibox-vec.c \
			   submodules/c_vt100utils/tuibox-vec.h

########################################################
setup-binaries:
	@mkdir -p ~/.bin
	@command -v passh || { cd submodules/passh/. && make && cp passh ~/.bin/.; }
	@command -v gtimeout || brew install coreutils
setup-golang:
	@command -v goimports || go install golang.org/x/tools/cmd/goimports@latest
setup-wg:
	@command -v wg || brew install wireguard-tools
