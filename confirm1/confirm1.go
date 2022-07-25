package main

import (
	"C"
	"fmt"

	"github.com/liamg/flinch/widgets"
)

func main() {}

//export DoConfirm
func DoConfirm() {

	confirmed, err := widgets.Confirm("Are you sure?")
	if err != nil {
		panic(err)
	}

	fmt.Printf("Confirmed: %t\n", confirmed)
}
