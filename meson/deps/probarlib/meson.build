probarlib_srcs = [files(
  '../../../submodules/probarlib/include/probar.h',
  '../../../submodules/probarlib/src/probar.c',
)]

probarlib_dirs = [
  '../../../submodules/probarlib',
  '../../../submodules/probarlib/images',
  '../../../submodules/probarlib/include',
  '../../../submodules/probarlib/src',
  inc,
]

probarlib_c_args = [
  '-Wno-format-security',
  ]
probarlib_deps = [

]

probarlib_lib =library('probarlib',
  probarlib_srcs,
  install: false,
  dependencies: probarlib_deps,
  include_directories: probarlib_dirs,
  c_args: probarlib_c_args,
)

probarlib_dep = declare_dependency(
  include_directories: probarlib_dirs,
  link_with: probarlib_lib,
)
