default: all
.PHONY: clean

CCFLAGS := -pthread
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CCFLAGS += -Wl,-no_pie
endif

init:
	[[ -d bin ]] || mkdir -p bin

clean:
	$(MAKE) -C go-adder clean
	$(MAKE) -C go-hello clean
	rm -f bin/* go-*/*.a

restic: init
	gcc $(CCFLAGS) -o bin/restic c-restic/c-restic.c go-restic/cmd/restic/go-restic.a -Igo-restic/cmd/restic

adder: init
	$(MAKE) -BC go-adder
	gcc $(CCFLAGS) -o bin/adder c-adder/adder.c go-adder/libadder.a -Igo-adder

#c-libadder: init adder
#	gcc $(CCFLAGS) -g -o bin/c-libadder.a c-libadder/c-libadder.c go-adder/libadder.a -Ic-libadder -Igo-adder

hello: init
	$(MAKE) -BC go-hello
	gcc $(CCFLAGS) -o bin/hello c-hello/hello.c go-hello/libhello.a -Igo-hello

build: hello adder

test:
	./bin/adder|bline -H -a 00ff00:ff0000
	./bin/hello|bline -H -a ff0000:00ff00

all: build test
