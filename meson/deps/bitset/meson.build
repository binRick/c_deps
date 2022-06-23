bitset_srcs = [files(
  '../../../submodules/bitset/include/cborg/bitset.h',
  '../../../submodules/bitset/src/bitset.c',
)]

bitset_dirs = [
  '../../../submodules/bitset',
  '../../../submodules/bitset/include',
  '../../../submodules/bitset/include/cborg',
  '../../../submodules/bitset/src',
  inc,
]

bitset_deps = [

]

bitset_lib = shared_library('bitset',
  bitset_srcs,
  install: false,
  dependencies: bitset_deps,
  include_directories: bitset_dirs,
)

bitset_dep = declare_dependency(
  include_directories: bitset_dirs,
  link_with: bitset_lib,
)
