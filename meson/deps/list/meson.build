list_dirs = [
   '../../../submodules/list/src',
   '../../../submodules/list',
    inc,
  ]
list_lib = static_library('list',
   '../../../submodules/list/src/list.c',
   '../../../submodules/list/src/list_iterator.c',
   '../../../submodules/list/src/list_node.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: list_dirs,
)
list_dep = declare_dependency(include_directories: list_dirs, link_with: list_lib)
