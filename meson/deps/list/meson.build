list_lib = static_library('list',
   '../../../submodules/list/src/list.c',
   '../../../submodules/list/src/list_iterator.c',
   '../../../submodules/list/src/list_node.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
   '../../../submodules/list/src',
  ]
)
list_dep = declare_dependency(include_directories: [inc], link_with: list_lib)
