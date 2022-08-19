libtrycatch_srcs = [files(
  '../../../submodules/libtrycatch/trycatch.c',
  '../../../submodules/libtrycatch/trycatch.h',
)]

libtrycatch_dirs = [
  '../../../submodules/libtrycatch',
  inc,
]

libtrycatch_deps = [

]

libtrycatch_lib = static_library('libtrycatch',
  libtrycatch_srcs,
  install: false,
  dependencies: libtrycatch_deps,
  include_directories: libtrycatch_dirs,
)

libtrycatch_dep = declare_dependency(
  include_directories: libtrycatch_dirs,
  link_with: libtrycatch_lib,
)
