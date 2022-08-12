default: all
include submodules/c_deps/etc/includes.mk
local-setup: setup-binaries setup-golang setup-wg setup
##############################################################
TIDIED_FILES = deps*/*.c deps*/*.h term*/*.c term*/*.h ctable*/*.c ctable*/*.h *table*/*.c *table*/*.h cgif-test/*.c *-test/*.c *-test/*.h chan-test/*.c chan-test/*.h \
			   introspect-test/*.c introspect-test/*.h \
			   introspect/*.c introspect/*.h \
			   reproc-test/*.c reproc-test/*.h \
			   list-test/*.c list-test/*.h \
			   *-test/*.c *-test/*.h \
			   intro*/*.c intro*/*.h \
			   exec-fzf*/*.c exec-fzf*/*.h \
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
