libspinner_test_srcs = [
  'libspinner-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
libspinner_test_include_dirs = [
  '.',
  inc,
]
libspinner_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  libspinner_dep,
  c_stringfn_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
libspinner_test_c_args = [
]
libspinner_test_link_args = [
]

libspinner_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  libspinner_test_exec = executable('libspinner-test',
     libspinner_test_srcs,
     dependencies: libspinner_test_deps,
     include_directories: libspinner_test_include_dirs,
     link_args: libspinner_test_link_args,
     c_args: libspinner_test_c_args,
     install: false,
  )
  test('libspinner-test', 
    libspinner_test_exec, args: ['-v','-a'],
    workdir: libspinner_test_test_dir,
  )
endif
