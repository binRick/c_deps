bytes_inc = [
  inc,
]
bytes_lib = static_library('bytes', 
  pwd + '/submodules/bytes/bytes.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: bytes_inc,
)
bytes_dep = declare_dependency(
  include_directories: bytes_inc,
  link_with: bytes_lib,
)
