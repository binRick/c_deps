bytes_inc = [
  inc,
]
bytes_lib_static =static_library('bytes', 
  c_deps_dir + '/submodules/bytes/bytes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: bytes_inc,
)
bytes_lib =shared_library('bytes', 
  c_deps_dir + '/submodules/bytes/bytes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: bytes_inc,
)
bytes_dep = declare_dependency(
  include_directories: bytes_inc,
  link_with: bytes_lib,
)
