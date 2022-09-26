lodepng_srcs = [
  'lodepng.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

lodepng_include_dirs = [
  '.',
  inc,
]

lodepng_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
]

lodepng_c_args = [
]

lodepng_link_args = [
]

lodepng_lib = library('lodepng',
  lodepng_srcs,
  install: false,
  dependencies: lodepng_deps,
  c_args: lodepng_c_args,
  include_directories: lodepng_include_dirs
)

lodepng_dep = declare_dependency(
  include_directories: lodepng_include_dirs,
  link_with: lodepng_lib,
  link_args: lodepng_link_args,
)
