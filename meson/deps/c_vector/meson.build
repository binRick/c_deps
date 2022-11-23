c_vector_inc = [
  '../../../submodules/c_vector/vector',
  '../../../submodules/c_vector',
  inc,
]
c_vector_c_args = [
  '-Wno-unused-parameter',
  ]
c_vector_lib_static =static_library('c_vector', 
  '../../../submodules/c_vector/vector/vector.c',
  install: false, 
  link_whole: hash_lib_static,
  dependencies: [
  ], 
  include_directories: c_vector_inc,
  c_args: c_vector_c_args,
)
c_vector_lib =shared_library('c_vector', 
  '../../../submodules/c_vector/vector/vector.c',
  install: false, 
  dependencies: [
    hash_dep,
  ], 
  include_directories: c_vector_inc,
  c_args: c_vector_c_args,
)
c_vector_dep = declare_dependency(
  include_directories: c_vector_inc,
  link_with: c_vector_lib,
)
