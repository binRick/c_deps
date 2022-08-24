c_img_srcs = [files(
  '../../../submodules/c_img/src/img.c',
)]

c_img_dirs = [
  '../../../submodules/c_img',
  '../../../submodules/c_img/src',
  inc,
]

c_img_deps = [

]

c_img_lib = static_library('c_img',
  c_img_srcs,
  install: false,
  dependencies: c_img_deps,
  include_directories: c_img_dirs,
)

c_img_dep = declare_dependency(
  include_directories: c_img_dirs,
  link_with: c_img_lib,
)
