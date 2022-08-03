probarlib_srcs = [files(
  '../../../submodules/probarlib/src/probar.c',
)]

probarlib_dirs = [
  '../../../submodules/probarlib',
  '../../../submodules/probarlib/include',
  '../../../submodules/probarlib/src',
  inc,
]

probarlib_deps = [

]

probarlib_lib = static_library('probarlib',
  probarlib_srcs,
  install: false,
  dependencies: probarlib_deps,
  include_directories: probarlib_dirs,
)

probarlib_dep = declare_dependency(
  include_directories: probarlib_dirs,
  link_with: probarlib_lib,
)
