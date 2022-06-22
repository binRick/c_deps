sqxc_test_srcs = [
  'sqxc-test.c',
]
sqxc_test_inc = [
 '/usr/local/include/sqxc',
 '../submodules/sqxclib',
 '../submodules/sqxclib/sqxc',
 '../submodules/sqxclib/sqxcapp',
 '../submodules/sqxclib/sqxcsupport',
 inc,
 '.',
]
sqxc_test_deps = [
 sqxclib_dep,
 jsonc_dep,
 sqlite_dep,
]

if get_option('enable-binaries')
  sqxc_test_exec = executable('sqxc-test', 
     sqxc_test_srcs,
     dependencies: sqxc_test_deps,
     include_directories: sqxc_test_inc,
  )
  if get_option('enable-binary-tests')
    test('sqxc-test', sqxc_test_exec, args: [])
  endif
endif
