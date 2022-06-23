csplit_srcs = [files(
  '../../../submodules/csplit/csplit.h',
)]

csplit_dirs = [
  '../../../submodules/csplit',
  inc,
]

csplit_deps = [

]

csplit_lib = shared_library('csplit',
  csplit_srcs,
  install: false,
  dependencies: csplit_deps,
  include_directories: csplit_dirs,
)

csplit_dep = declare_dependency(
  include_directories: csplit_dirs,
  link_with: csplit_lib,
)
