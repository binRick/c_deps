sqxc_test_srcs = [
  'sqxc-test.c',
]
sqxc_test_inc = [
 '.',
 inc,
]
sqxc_test_c_args = [
  '-I/usr/local/include/sqxc',
  '-I/usr/local/include/sqxc//app',
  '-I/usr/local/include/sqxc/support',
  '-I/usr/local/share/sqxclib/project-template/sqxcapp',
  '-L/usr/local/lib',
  '-L/usr/local/Cellar/json-c/0.16/lib','-L/usr/local/lib',
  '-lsqxcapptool','-lsqxcsupport','-lsqxcapp','-lsqxc_sqlite',
  '-lsqxcpp','-lsqxc-lsqlite3','-ljson-c',
  ]
sqxc_test_deps = [
  sqxclib_dep,
  #jsonc_dep,
  #sqlite3_dep,
]

if get_option('enable-binaries')
  sqxc_test_exec = executable('sqxc-test', 
     sqxc_test_srcs,
     dependencies: sqxc_test_deps,
     include_directories: sqxc_test_inc,
     c_args: sqxc_test_c_args,
  )
  if get_option('enable-binary-tests')
    #   test('sqxc-test', sqxc_test_exec, args: [])
 #   test('view-schema', sh_program, args: ['-c', 'sqlite3 .sqxc-test.sqlite <<< ".schema"'])
  endif
endif
