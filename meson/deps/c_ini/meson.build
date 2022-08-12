c_ini_srcs = [files(
  '../../../submodules/c_ini/include/ini.h',
  '../../../submodules/c_ini/src/ini.c',
)]

c_ini_dirs = [
  '../../../submodules/c_ini',
  '../../../submodules/c_stringfn/include',
  '../../../submodules/c_stringfn/src',
  '../../../submodules/c_stringfn',
  '../../../submodules/c_fsio',
  '../../../submodules/c_fsio/include',
  '../../../submodules/c_fsio/src',
  '../../../submodules/c_string_buffer',
  '../../../submodules/c_string_buffer/src',
  '../../../submodules/c_string_buffer/include',
  '../../../submodules/c_vector/include',
  '../../../submodules/c_vector',
  '../../../submodules/c_vector/src',
  '../../../submodules/c_ini/include',
  '../../../submodules/c_ini/src',
  inc,
]

c_ini_deps = [
  c_vector_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  c_fsio_dep,
]

c_ini_lib = library('c_ini',
  c_ini_srcs,
  install: false,
  dependencies: c_ini_deps,
  include_directories: c_ini_dirs,
)

c_ini_dep = declare_dependency(
  include_directories: c_ini_dirs,
  link_with: c_ini_lib,
)
