path_join_lib = both_libraries('path-join',
  pwd + '/submodules/path-join.c/src/path-join.c',
  install: false, 
  dependencies: [
    str_ends_with_dep,
  ], 
  include_directories: [
    inc,
  ]
)
path_join_dep = declare_dependency(include_directories: [inc], link_with: path_join_lib)
