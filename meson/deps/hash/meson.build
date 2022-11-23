hash_srcs = [files(
  '../../../submodules/hash/hash.c',
)]

hash_dirs = [
  '../../../submodules/hash',
  inc,
]

hash_deps = [

]
hash_lib_static =static_library('hash',
  hash_srcs,
  install: false,
  dependencies: hash_deps,
  include_directories: hash_dirs,
)

hash_lib =shared_library('hash',
  hash_srcs,
  install: false,
  dependencies: hash_deps,
  include_directories: hash_dirs,
)

hash_dep = declare_dependency(
  include_directories: hash_dirs,
  link_with: hash_lib,
)
