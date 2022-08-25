.PHONY: clean

libhello.a:
	[[ -f go.mod ]] || go mod init hello
	go mod tidy
	goimports -w hello.go
	go get
	go build -buildmode=c-archive -o $@

clean:
	rm -f libhello.a go.sum go.mod libhello.h
