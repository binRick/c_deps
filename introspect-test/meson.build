introspect_test_srcs = [
  'introspect-test.c',
]
introspect_test_inc = [
 inc,
 '.',
]
introspect_test_deps = [
 reproc_dep,
 list_dep,
 ansicodes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 greatest_dep,
 ansicodes_dep,
 logh_dep,
 introspect_dep,
]

if get_option('enable-binaries')
  introspect_test_exec = executable('introspect-test', 
     introspect_test_srcs,
     dependencies: introspect_test_deps,
     include_directories: introspect_test_inc,
  )
  if get_option('enable-binary-tests')
    test('introspect-test', introspect_test_exec, args: [])
  endif
endif
