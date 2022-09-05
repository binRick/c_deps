tinydir_test_srcs = [
  'tinydir-test.c',
]
tinydir_test_inc = [
 inc,
 '../tinydir-test',
]
tinydir_test_deps = [
 tinydir_dep,
 tinydir_dep,
 ansi_codes_dep,
 c_fsio_dep,
 c_stringfn_dep,
 c_string_buffer_dep,
 c_greatest_dep,
 log_dep,
 tinydir_dep,
]

if get_option('enable-binaries')
  tinydir_test_exec = executable('tinydir-test', 
     tinydir_test_srcs,
     dependencies: tinydir_test_deps,
     include_directories: tinydir_test_inc,
  )
  if get_option('enable-binary-tests')
    test('tinydir-test', tinydir_test_exec, args: [])
  endif
endif
