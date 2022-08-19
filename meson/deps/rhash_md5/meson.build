rhash_md5_inc = [
  '../../../submodules/rhash_md5.c',
  inc,
]
rhash_md5_lib = static_library('rhash_md5', 
  '../../../submodules/rhash_md5.c/md5.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: rhash_md5_inc,
)
rhash_md5_dep = declare_dependency(
  include_directories: rhash_md5_inc,
  link_with: rhash_md5_lib,
)
