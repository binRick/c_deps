default: all
.PHONY: clean
CCFLAGS := -pthread -Iadder -Ihello
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	# This prevents a warning about PIE on Mac OS
	CCFLAGS += -Wl,-no_pie
endif


clean:
	$(MAKE) -C go_adder clean
	$(MAKE) -C go_hello clean
	rm -f c_adder c_hello

c_adder: 
	$(MAKE) -C go_adder
	gcc $(CCFLAGS) -o c_adder c_adder.c  go_adder/libadder.a

c_hello: go_hello
	$(MAKE) -C go_hello
	gcc $(CCFLAGS) -o c_hello c_hello.c  go_hello/libhello.a

build: c_hello c_adder

test:
	./c_adder
	./c_hello

all: clean build test
