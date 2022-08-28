
gofmt -w select_description1.go select_description1
go mod init
go mod tidy
go build -o select_description1.a -buildmode=c-archive
gcc -o select_description1 select_description1.c select_description1.a
