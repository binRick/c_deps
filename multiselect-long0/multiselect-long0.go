package main

import "C"

import (
	"fmt"
	"strings"
	"unsafe"

	"github.com/liamg/flinch/widgets"
)

type Foo struct{ a, b int32 }

func main() {}
func strings_to_cchars(items []string) **C.char {
	cArray := C.malloc(C.size_t(len(items)) * C.size_t(unsafe.Sizeof(uintptr(0))))

	// convert the C array to a Go Array so we can index it
	a := (*[1<<30 - 1]*C.char)(cArray)

	for idx, substring := range items {
		a[idx] = C.CString(substring)
	}

	return (**C.char)(cArray)

}

//export TestStrings0
func TestStrings0(ss []string) {
	fmt.Println("TestStrings0 Called")
	for i, val := range ss {
		fmt.Printf("  - >%d/%d: %s|%s\n", i+1, len(ss), val, ss[i])
	}

}

//export GetStrings
func GetStrings(ss []string) **C.char {
	fmt.Println("GetStrings Called")
	fmt.Println("%d strings", len(ss))
	for i, val := range ss {
		fmt.Printf("  - >%d/%d: %s|%s\n", i+1, len(ss), val, ss[i])
	}
	items := []string{
		"xxxxxxxxxx",
		"yyyyyyyyyy",
	}
	return (strings_to_cchars(items))
}

//export TestStrings
func TestStrings(ss []string) {
	fmt.Println("TestStrings Called")
	fmt.Println("%d strings", len(ss))
	for i, val := range ss {
		fmt.Printf("  - >%d/%d: %s|%s\n", i+1, len(ss), val, ss[i])
	}

}

//export TestRunes
func TestRunes(ss []rune) {
	fmt.Println("TestRunes Called")
	for i, val := range ss {
		fmt.Printf("  - >%d/%d: %s\n", i+1, len(ss), string(val))
	}

}

//export TestInts
func TestInts(is []int) {
	fmt.Println("TestInts Called")
	for i, val := range is {
		fmt.Printf("  - >%d/%d: %d\n", i+1, len(is), val)
	}

}

//export TestInt
func TestInt(i int) {
	fmt.Println("TestInt Called")
	fmt.Printf(">%d\n", i)

}

//export RegisterCallback
func RegisterCallback(funcptr unsafe.Pointer) {
	//cstr := strings_to_cchars([]string{"a", "b"})
	//defer C.free(unsafe.Pointer(cstr))

	foo := *(*func())(funcptr)
	foo()
	fmt.Println("foo called")

	//fmt.Println(C.GoString((*C.char)(result)))
}

//export DoMultiSelectLong
func DoMultiSelectLong(title string, provided_options []int) **C.char {
	fmt.Printf("You provided %d options- .\n", len(provided_options))
	//, strings.Join(po, ", "))
	var options = []string{}
	for i := 0; i < 100; i++ {
		options = append(options, fmt.Sprintf("Option %d", i))
	}

	_, items, err := widgets.MultiSelect(
		title,
		options,
	)
	if err == widgets.ErrInputCancelled {
		fmt.Println("User cancelled.")
		return (strings_to_cchars([]string{}))
	}

	fmt.Printf("You selected %s.\n", strings.Join(items, ", "))
	return (strings_to_cchars(items))
}
