ee_test_srcs = [
  'ee-test.c',
]
ee_test_inc = [
 inc,
]
ee_test_deps = [
 ee_dep,
 list_dep,
 c_greatest_dep,
 ansi_codes_dep,
 logh_dep,
]

if get_option('enable-binaries')
  ee_test_exec = executable('ee-test', 
     ee_test_srcs,
     dependencies: ee_test_deps,
     include_directories: ee_test_inc,
  )
  if get_option('enable-binary-tests')
    test('ee-test', ee_test_exec, args: [])
  endif
endif
