dotenv_test_srcs = [
  'dotenv-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
dotenv_test_include_dirs = [
  '.',
  inc,
]
dotenv_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  dotenv_c_dep,
  ansi_codes_dep,
  logh_dep,
  timestamp_dep,
]
dotenv_test_c_args = [
]
dotenv_test_link_args = [
]

dotenv_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  dotenv_test_exec = executable('dotenv-test',
     dotenv_test_srcs,
     dependencies: dotenv_test_deps,
     include_directories: dotenv_test_include_dirs,
     link_args: dotenv_test_link_args,
     c_args: dotenv_test_c_args,
     install: false,
  )
  test('dotenv-test', 
    dotenv_test_exec, args: ['-v','-a'],
    workdir: dotenv_test_test_dir,
  )
endif
