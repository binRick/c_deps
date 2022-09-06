sqxc_test_srcs = [
  'sqxc-test.c',
]
sqxc_test_inc = [
 '.',
 inc,
]
sqxc_test_deps = [
 sqxclib_dep,
 jsonc_dep,
 sqlite3_dep,
]

if get_option('enable-binaries')
  sqxc_test_exec = executable('sqxc-test', 
     sqxc_test_srcs,
     dependencies: sqxc_test_deps,
     include_directories: sqxc_test_inc,
  )
  if get_option('enable-binary-tests')
    #   test('sqxc-test', sqxc_test_exec, args: [])
 #   test('view-schema', sh_program, args: ['-c', 'sqlite3 .sqxc-test.sqlite <<< ".schema"'])
  endif
endif
