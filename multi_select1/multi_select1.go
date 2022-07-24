package main

import "C"

import (
	"fmt"
	"unsafe"

	survey "github.com/AlecAivazis/survey/v2"
)

// the questions to ask
var Options = []string{
	"Afghanistan",
	"Åland Islands",
	"Albania",
	"Algeria",
	"American Samoa",
	"AndorrA",
	"Angola",
	"Anguilla",
	"Antarctica",
	"Antigua and Barbuda",
	"Argentina",
	"Armenia",
	"Aruba",
	"Australia",
	"Austria",
	"Azerbaijan",
	"Bahamas",
	"Bahrain",
	"Bangladesh",
	"Barbados",
	"Belarus",
	"Belgium",
	"Belize",
	"Benin",
	"Bermuda",
	"Bhutan",
	"Bolivia",
	"Bosnia and Herzegovina",
	"Botswana",
	"Bouvet Island",
	"Brazil",
	"British Indian Ocean Territory",
	"Brunei Darussalam",
	"Bulgaria",
	"Burkina Faso",
	"Burundi",
	"Cambodia",
	"Cameroon",
	"Canada",
	"Cape Verde",
	"Cayman Islands",
	"Central African Republic",
	"Chad",
	"Chile",
	"China",
	"Christmas Island",
	"Cocos (Keeling) Islands",
	"Colombia",
	"Comoros",
	"Congo",
	"Congo, The Democratic Republic of the",
	"Cook Islands",
	"Costa Rica",
	"Cote D'Ivoire",
	"Croatia",
	"Cuba",
	"Cyprus",
	"Czech Republic",
	"Denmark",
	"Djibouti",
	"Dominica",
	"Dominican Republic",
	"Ecuador",
	"Egypt",
	"El Salvador",
	"Equatorial Guinea",
	"Eritrea",
	"Estonia",
	"Ethiopia",
	"Falkland Islands (Malvinas)",
	"Faroe Islands",
	"Fiji",
	"Finland",
	"France",
	"French Guiana",
	"French Polynesia",
	"French Southern Territories",
	"Gabon",
	"Gambia",
	"Georgia",
	"Germany",
}

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

//export DoMultiSelectArray
func DoMultiSelectArray(title string) **C.char {
	answers := []string{}
	var multiQs = []*survey.Question{
		{
			Name: "letter",
			Prompt: &survey.MultiSelect{
				Message: title,
				Options: Options,
			},
		},
	}
	err := survey.Ask(multiQs, &answers)
	if err != nil {
		fmt.Println(err.Error())
	}
	return (strings_to_cchars(answers))
}
