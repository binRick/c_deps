reproc_test_srcs = [
  'reproc-test.c',
]
reproc_test_inc = [
 inc,
 '../reproc-test',
]
reproc_test_deps = [
 reproc_dep,
 list_dep,
 ansicodes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 greatest_dep,
 ansicodes_dep,
 logh_dep,
]

if get_option('enable-binaries')
  reproc_test_exec = executable('reproc-test', 
     reproc_test_srcs,
     dependencies: reproc_test_deps,
     include_directories: reproc_test_inc,
  )
  if get_option('enable-binary-tests')
    test('reproc-test', reproc_test_exec, args: [])
  endif
endif
