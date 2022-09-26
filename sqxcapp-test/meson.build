sqxcapp_test_srcs = [
  'sqxcapp-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
sqxcapp_test_include_dirs = [
  '.',
  inc,
]
sqxcapp_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  sqxclib_dep,
]
sqxcapp_test_c_args = [
  '-I/usr/local/include/sqxc',
  '-I/usr/local/include/sqxc//app',
  '-I/usr/local/include/sqxc/support',
  '-I/usr/local/share/sqxclib/project-template/sqxcapp',
  '-L/usr/local/lib',
  '-L/usr/local/Cellar/json-c/0.16/lib','-L/usr/local/lib',
]
sqxcapp_test_link_args = [
  '-lsqxcapptool','-lsqxcsupport','-lsqxcapp','-lsqxc_sqlite',
  '-lsqxcpp',
  '-lsqxc','-lsqlite3',
  '-ljson-c',
  '-lsqxcapp',
]

sqxcapp_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  sqxcapp_test_exec = executable('sqxcapp-test',
     sqxcapp_test_srcs,
     dependencies: sqxcapp_test_deps,
     include_directories: sqxcapp_test_include_dirs,
     link_args: sqxcapp_test_link_args,
     c_args: sqxcapp_test_c_args,
     install: false,
  )
  test('sqxcapp-test', 
    sqxcapp_test_exec, args: ['-v','-a'],
    workdir: sqxcapp_test_test_dir,
  )
endif
