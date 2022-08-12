siphash_srcs = [files(
  '../../../submodules/siphash/halfsiphash.c',
  '../../../submodules/siphash/halfsiphash.h',
  '../../../submodules/siphash/siphash.c',
  '../../../submodules/siphash/siphash.h',
  '../../../submodules/siphash/vectors.h',
)]

siphash_dirs = [
  '../../../submodules/siphash',
  inc,
]

siphash_deps = [

]

siphash_lib = both_libraries('siphash',
  siphash_srcs,
  install: false,
  dependencies: siphash_deps,
  include_directories: siphash_dirs,
)

siphash_dep = declare_dependency(
  include_directories: siphash_dirs,
  link_with: siphash_lib,
)
