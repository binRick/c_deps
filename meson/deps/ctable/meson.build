ctable_lib = library('ctable',
  pwd + '/submodules/ctable/src/table.c',
  pwd + '/submodules/ctable/src/constraint.c',
  pwd + '/submodules/ctable/src/alloc_wrappers.c',
  pwd + '/submodules/ctable/src/string_util.c',
  pwd + '/submodules/ctable/src/printing.c',
  pwd + '/submodules/ctable/src/vector.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
ctable_dep = declare_dependency(include_directories: [inc], link_with: ctable_lib)
