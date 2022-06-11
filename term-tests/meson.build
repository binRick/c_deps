term_tests_srcs = [
  'term-tests.c',
]

term_tests_include_dirs = [
    inc,
  '../submodules/termpaint',
  '../',
  '../submodules',
]

term_tests_deps = [
  c_stringfn_dep,  
  c_stringfn_dep,  
  termpaint_dep,  
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
