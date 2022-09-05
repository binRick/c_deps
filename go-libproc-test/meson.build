go_libproc_test_srcs = [
  'go-libproc-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
go_libproc_test_include_dirs = [
  '.',
  inc,
]
go_libproc_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  go_libproc_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
go_libproc_test_c_args = [
]
go_libproc_test_link_args = [
]

go_libproc_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  go_libproc_test_exec = executable('go-libproc-test',
     go_libproc_test_srcs,
     dependencies: go_libproc_test_deps,
     include_directories: go_libproc_test_include_dirs,
     link_args: go_libproc_test_link_args,
     c_args: go_libproc_test_c_args,
     install: false,
  )
  test('go-libproc-test', 
    go_libproc_test_exec, args: ['-v','-a'],
    workdir: go_libproc_test_test_dir,
  )
endif
