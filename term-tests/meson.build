term_tests_srcs = [
  'term-tests.c',
]

term_tests_include_dirs = [
    inc,
]

term_tests_deps = [
  termpaint_dep,  
  c_stringfn_dep,  
  c_string_buffer_dep,  
  ansi_codes_dep,  
  timestamp_dep,  
]

term_tests_lib = library('term-tests',
  term_tests_srcs,
  install: false,
  dependencies: term_tests_deps,
  include_directories: [
    term_tests_include_dirs,
  ],
)

term_tests_dep = declare_dependency(
  include_directories: term_tests_include_dirs,
  link_with: term_tests_lib,
)
