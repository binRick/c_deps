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
  generic_print_dep,
  murmurhash_dep,
  libbeaufort_dep,
  bitset_dep,
  c_dt_dep,
  bestline_dep,
  layout_dep,
  csplit_dep,
  subhook_dep,
  socket99_dep,
  flingfd_dep,
  env_h_dep,
  throw_h_dep,
  c_timestamp_dep,
  c_forever_dep,
  dbg_dep,
  c_eventemitter_dep,
  c_workqueue_dep,
  microtar_dep,
  dmt_dep,
  microui_dep,
  catpath_dep,
  str_truncate_dep,
  vtparse_dep,
  cansid_dep,
  ansi_utils_dep,
  http_get_dep,
]
deps_link_args = [
]
if get_option('enable-binaries')
  deps_test_exec = executable('deps-test',
     deps_test_srcs,
     dependencies: deps_test_deps,
     include_directories: deps_include_dirs,
     link_args: deps_link_args,
     install: true,
     pie: true,
  )
  if get_option('enable-binary-tests')
    test('deps-test', 
      passh_program, args: [deps_test_exec],
      timeout: 60,
      workdir: meson.current_source_dir(),
      verbose: true,
      )
  endif
endif
