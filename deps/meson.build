deps_srcs = [
  'deps.c',
]
deps_inc_dirs = [
  '../submodules',
  '../',
]
deps_args = [

]

deps_deps = [
  ansicodes_dep,
  asprintf_dep,
  assertf_dep,
  #b64_dep,
  bytes_dep,
  c_fsio_dep,
  c_string_buffer_dep,
  c_stringfn_dep,
  #  c_timer_dep,
  cargs_dep,
  chan_dep,
  cstructs_json_dep,
  debug_print_h_dep,
  dbg_dep,
  debug_memory_dep,
  djbhash_dep,
  fs_dep,
  generic_print_dep,
  greatest_dep,
  http_get_dep,
  incbin_dep,
  libyaml_dep,
  module_dep,
  ms_dep,
  #  occurrences_dep,
  parson_dep,
  progress_dep,
  rgba_dep,
  smaz_dep,
  sqlite_dep,
  strdup_dep,
  tempdir_dep,
  termpaint_dep,
  timestamp_dep,
  libmutotp_dep,
  progressbar_dep,
  curses_dep,
  cansid_dep,
  slug_dep,
  which_dep,
  libspinner_dep,
]

deps_lib = static_library('deps',
  deps_srcs,
  install: false,
  dependencies: deps_deps,
  include_directories: deps_inc_dirs,
  c_args: deps_args,
)

deps_dep = declare_dependency(
  include_directories: deps_inc_dirs,
  link_with: deps_lib,
)
