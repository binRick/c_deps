deps_test_srcs = [
  'deps-test.c',
]
deps_include_dirs = [
  inc,
]
deps_test_deps = [
  deps_dep,
  occurrences_dep,
  str_replace_dep,
]

if get_option('enable-binaries')
  deps_test_exec = executable('deps-test',
     deps_test_srcs,
     dependencies: deps_test_deps,
     include_directories: deps_include_dirs,
  )
  if get_option('enable-binary-tests')
    test('deps-test', deps_test_exec, args: [])
  endif
endif
