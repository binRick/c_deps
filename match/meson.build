match_srcs = [
  'match.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

match_include_dirs = [
  '.',
  inc,
]

match_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  wildcardcmp_dep,
  module_dep,
  bytes_dep,
  tinydir_dep,
]

match_c_args = [
]

match_link_args = [
]

match_lib = library('match',
  match_srcs,
  install: false,
  dependencies: match_deps,
  c_args: match_c_args,
  include_directories: match_include_dirs
)

match_dep = declare_dependency(
  include_directories: match_include_dirs,
  link_with: match_lib,
  link_args: match_link_args,
)
