sha256_c_srcs = [files(
  '../../../submodules/sha256.c/sha256.c',
)]

sha256_c_dirs = [
  '../../../submodules/sha256.c',
  '../../../submodules',
  inc,
]

sha256_c_deps = [
  rotate_bits_dep,
]

sha256_c_lib =library('sha256-c',
  sha256_c_srcs,
  install: false,
  dependencies: sha256_c_deps,
  include_directories: sha256_c_dirs,
)

sha256_c_dep = declare_dependency(
  include_directories: sha256_c_dirs,
  link_with: sha256_c_lib,
)
