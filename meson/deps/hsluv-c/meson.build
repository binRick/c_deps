hsluv_c_srcs = [files(
  '../../../submodules/hsluv-c/src/hsluv.c',
  '../../../submodules/hsluv-c/src/hsluv.h',
)]

hsluv_c_dirs = [
  '../../../submodules/hsluv-c',
  '../../../submodules/hsluv-c/src',
  inc,
]

hsluv_c_deps = [

]

hsluv_c_lib =library('hsluv-c',
  hsluv_c_srcs,
  install: false,
  dependencies: hsluv_c_deps,
  include_directories: hsluv_c_dirs,
)

hsluv_c_dep = declare_dependency(
  include_directories: hsluv_c_dirs,
  link_with: hsluv_c_lib,
)
