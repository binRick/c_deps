c_vector_inc = [
  '../../../submodules/c_vector/include',
  '../../../submodules/c_vector/src',
  '../../../submodules/c_vector',
  inc,
]
c_vector_lib = library('c_vector', 
  '../../../submodules/c_vector/src/vector.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: c_vector_inc,
)
c_vector_dep = declare_dependency(
  include_directories: c_vector_inc,
  link_with: c_vector_lib,
)
