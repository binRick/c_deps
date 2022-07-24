c89atomic_srcs = [files(
  '../../../submodules/c89atomic/c89atomic.h',
)]

c89atomic_dirs = [
  '../../../submodules/c89atomic',
  inc,
]

c89atomic_deps = [

]

c89atomic_lib = library('c89atomic',
  c89atomic_srcs,
  install: false,
  dependencies: c89atomic_deps,
  include_directories: c89atomic_dirs,
)

c89atomic_dep = declare_dependency(
  include_directories: c89atomic_dirs,
  link_with: c89atomic_lib,
)
