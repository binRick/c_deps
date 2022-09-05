socket99_test_srcs = [
  'socket99-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
socket99_test_include_dirs = [
  '.',
  inc,
]
socket99_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  socket99_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
socket99_test_c_args = [
]
socket99_test_link_args = [
]

socket99_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  socket99_test_exec = executable('socket99-test',
     socket99_test_srcs,
     dependencies: socket99_test_deps,
     include_directories: socket99_test_include_dirs,
     link_args: socket99_test_link_args,
     c_args: socket99_test_c_args,
     install: false,
  )
  test('socket99-test', 
    socket99_test_exec, args: ['-v','-a'],
    workdir: socket99_test_test_dir,
  )
endif
