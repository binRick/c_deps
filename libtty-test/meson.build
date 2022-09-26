libtty_test_srcs = [
  'libtty-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libtty_test_include_dirs = [
  '.',
  inc,
]
libtty_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  termrec_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]
libtty_test_c_args = [
]
libtty_test_link_args = [
]

libtty_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libtty_test_exec = executable('libtty-test',
     libtty_test_srcs,
     dependencies: libtty_test_deps,
     include_directories: libtty_test_include_dirs,
     link_args: libtty_test_link_args,
     c_args: libtty_test_c_args,
     install: false,
  )
  test('libtty-test', 
    libtty_test_exec, args: ['-v','-a'],
    workdir: libtty_test_test_dir,
  )
endif
