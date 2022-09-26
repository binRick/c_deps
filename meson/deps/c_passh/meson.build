c_passh_srcs = [files(
  '../../../submodules/c_passh/passh.c',
)]

c_passh_dirs = [
  '../../../submodules/c_passh',
  inc,
]

c_passh_deps = [

]

c_passh_lib =library('c_passh',
  c_passh_srcs,
  install: false,
  dependencies: c_passh_deps,
  c_args: ['-DPASSH_LIB'],
  include_directories: c_passh_dirs,
)

c_passh_dep = declare_dependency(
  include_directories: c_passh_dirs,
  link_with: c_passh_lib,
)
