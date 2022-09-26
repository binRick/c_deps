libyuarel_srcs = [files(
  '../../../submodules/libyuarel/yuarel.c',
)]

libyuarel_dirs = [
  '../../../submodules/libyuarel',
  inc,
]

libyuarel_deps = [

]

libyuarel_lib =library('libyuarel',
  libyuarel_srcs,
  install: false,
  dependencies: libyuarel_deps,
  include_directories: libyuarel_dirs,
)

libyuarel_dep = declare_dependency(
  include_directories: libyuarel_dirs,
  link_with: libyuarel_lib,
)
