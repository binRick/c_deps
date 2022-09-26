.PHONY: clean

libui.a:
	[[ -f go.mod ]] || go mod init ui
	goimports -w ui.go
	go build  -ldflags '-w -extldflags "-static"' -buildmode=c-archive -o $@

clean:
	rm -f libui.* go.mod
