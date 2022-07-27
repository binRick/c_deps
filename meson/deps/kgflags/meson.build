kgflags_srcs = [files(
  '../../../submodules/kgflags/kgflags.h',
)]

kgflags_dirs = [
  '../../../submodules/kgflags',
  inc,
]

kgflags_deps = [

]

kgflags_lib = shared_library('kgflags',
  kgflags_srcs,
  install: false,
  dependencies: kgflags_deps,
  include_directories: kgflags_dirs,
)

kgflags_dep = declare_dependency(
  include_directories: kgflags_dirs,
  link_with: kgflags_lib,
)
