list_test_srcs = [
  'list-test.c',
]
list_test_inc = [
 inc,
 '../list-test',
]
list_test_deps = [
 list_dep,
 list_dep,
 ansi_codes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 c_greatest_dep,
 logh_dep,
 list_dep,
]

if get_option('enable-binaries')
  list_test_exec = executable('list-test', 
     list_test_srcs,
     dependencies: list_test_deps,
     include_directories: list_test_inc,
  )
  if get_option('enable-binary-tests')
    test('list-test', list_test_exec, args: [])
  endif
endif
