msgbox_test_srcs = [
  'msgbox-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
msgbox_test_include_dirs = [
  '.',
  inc,
]
msgbox_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  msgbox_dep,
  timestamp_dep,
  ms_dep,
  bytes_dep,
]
msgbox_test_c_args = [
]
msgbox_test_link_args = [
]

msgbox_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  msgbox_test_exec = executable('msgbox-test',
     msgbox_test_srcs,
     dependencies: msgbox_test_deps,
     include_directories: msgbox_test_include_dirs,
     link_args: msgbox_test_link_args,
     c_args: msgbox_test_c_args,
     install: false,
  )
  test('msgbox-test', 
    msgbox_test_exec, args: ['-v','-a'],
    workdir: msgbox_test_test_dir,
  )
endif
