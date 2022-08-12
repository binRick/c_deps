vtparse_inc = [
  '../../../submodules/vtparse',
  '../../../submodules/vtparse/vtparse',
  inc,
]
vtparse_lib = both_libraries('vtparse', 
  '../../../submodules/vtparse/vtparse/vtparse.c',
  '../../../submodules/vtparse/vtparse/vtparse_table.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: vtparse_inc,
)
vtparse_dep = declare_dependency(
  include_directories: vtparse_inc,
  link_with: vtparse_lib,
)
