c_fsio_inc = [
  inc,
]
c_fsio_lib = library('c_fsio', 
  meson_deps_dir + '/submodules/c_fsio/src/fsio.c',
  install: false, 
  dependencies: [
    c_string_buffer_dep,
  ], 
  include_directories: c_fsio_inc,
)
c_fsio_dep = declare_dependency(
  include_directories: c_fsio_inc,
  link_with: c_fsio_lib,
)
