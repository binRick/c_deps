alloc_or_die_srcs = [files(
  '../../../submodules/alloc_or_die/alloc_or_die.c',
)]

alloc_or_die_dirs = [
  '../../../submodules/alloc_or_die',
  inc,
]

alloc_or_die_deps = [

]

alloc_or_die_lib =library('alloc_or_die',
  alloc_or_die_srcs,
  install: false,
  dependencies: alloc_or_die_deps,
  include_directories: alloc_or_die_dirs,
)

alloc_or_die_dep = declare_dependency(
  include_directories: alloc_or_die_dirs,
  link_with: alloc_or_die_lib,
)
