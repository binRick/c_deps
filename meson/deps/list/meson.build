list_lib = static_library('list',
  pwd + '/submodules/list/src/list.c',
  pwd + '/submodules/list/src/list_iterator.c',
  pwd + '/submodules/list/src/list_node.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
list_dep = declare_dependency(include_directories: [inc], link_with: list_lib)
