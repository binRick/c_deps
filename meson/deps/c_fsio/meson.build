c_fsio_inc = [
  '../../../submodules/c_fsio',
  '../../../submodules/c_fsio/include',
  '../../../submodules/c_fsio/src',
  inc,
]
c_fsio_lib = static_library('c_fsio', 
  c_deps_dir +  '/submodules/c_fsio/src/fsio.c',
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
