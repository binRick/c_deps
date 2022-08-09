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
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 c_greatest_dep,
 ansi_codes_dep,
 logh_dep,
 introspect_dep,
 parson_dep,
 ee_dep,
 debug_memory_dep,
]

if get_option('enable-binaries')
  introspect_test_exec = executable('introspect-test', 
     introspect_test_srcs,
     dependencies: introspect_test_deps,
     include_directories: introspect_test_inc,
  )
  if get_option('enable-binary-tests')
    #    test('introspect-test', passh_program, args: [introspect_test_exec,'-v','-a'])
  endif
endif
