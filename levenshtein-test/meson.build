levenshtein_test_srcs = [
  'levenshtein-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
levenshtein_test_include_dirs = [
  '.',
  inc,
]
levenshtein_test_deps = [
  c_greatest_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  levenshtein_dep,
  ansi_codes_dep,
  log_dep,
  timestamp_dep,
]
levenshtein_test_c_args = [
]
levenshtein_test_link_args = [
]

levenshtein_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  levenshtein_test_exec = executable('levenshtein-test',
     levenshtein_test_srcs,
     dependencies: levenshtein_test_deps,
     include_directories: levenshtein_test_include_dirs,
     link_args: levenshtein_test_link_args,
     c_args: levenshtein_test_c_args,
     install: false,
  )
  test('levenshtein-test', 
    levenshtein_test_exec, args: ['-v','-a'],
    workdir: levenshtein_test_test_dir,
  )
endif
