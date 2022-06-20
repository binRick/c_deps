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
  tiny_regex_c_dep,
  c_vector_dep,
  c_forever_dep,
  dbg_dep,
  c_eventemitter_dep,
  c_workqueue_dep,
  microtar_dep,
  dmt_dep,
  microui_dep,
  catpath_dep,
  str_truncate_dep,
]
deps_link_args = [
  #'-L/usr/local/lib',
  #'-LSDL2',
  #osx_ldflags,
  #,-lSDL2,-lm',
]
if get_option('enable-binaries')
  deps_test_exec = executable('deps-test',
     deps_test_srcs,
     dependencies: deps_test_deps,
     include_directories: deps_include_dirs,
     link_args: deps_link_args,
  )
  if get_option('enable-binary-tests')
    test('deps-test', deps_test_exec, args: [])
  endif
endif
