.PHONY: clean

libadder.a:
	[[ -f go.mod ]] || go mod init adder
	goimports -w adder.go
	go build -buildmode=c-archive -o $@

clean:
	rm -f libadder.* go.mod
