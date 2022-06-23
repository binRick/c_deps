mkcreflect_srcs = [files(
    '../../../submodules/mkcreflect/lib/include/mkcreflect.h',
)]

mkcreflect_dirs = [
  '../../../submodules/mkcreflect',
  '../../../submodules/mkcreflect/lib',
  '../../../submodules/mkcreflect/lib/include',
  inc,
]

mkcreflect_deps = [

]

mkcreflect_lib = library('mkcreflect',
  mkcreflect_srcs,
  install: false,
  dependencies: mkcreflect_deps,
  c_args: ['-DMKCREFLECT_IMPL'],
  include_directories: mkcreflect_dirs,
)

mkcreflect_dep = declare_dependency(
  include_directories: mkcreflect_dirs,
  link_with: mkcreflect_lib,
)
