semver_test_srcs = [
  'semver-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
semver_test_include_dirs = [
  '.',
  inc,
]
semver_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  semver_c_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
semver_test_c_args = [
]
semver_test_link_args = [
]

semver_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  semver_test_exec = executable('semver-test',
     semver_test_srcs,
     dependencies: semver_test_deps,
     include_directories: semver_test_include_dirs,
     link_args: semver_test_link_args,
     c_args: semver_test_c_args,
     install: false,
  )
  test('semver-test', 
    semver_test_exec, args: ['-v','-a'],
    workdir: semver_test_test_dir,
  )
endif
