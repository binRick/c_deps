murmurhash_inc = [
  '../../../submodules/murmurhash.c',
  inc,
]
murmurhash_lib = static_library('murmurhash', 
  '../../../submodules/murmurhash.c/murmurhash.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: murmurhash_inc,
)
murmurhash_dep = declare_dependency(
  include_directories: murmurhash_inc,
  link_with: murmurhash_lib,
)
