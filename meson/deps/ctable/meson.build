ctable_srcs = [
  c_deps_dir + '/submodules/ctable/src/table.c',
  c_deps_dir + '/submodules/ctable/src/constraint.c',
  c_deps_dir + '/submodules/ctable/src/alloc_wrappers.c',
  c_deps_dir + '/submodules/ctable/src/string_util.c',
  c_deps_dir + '/submodules/ctable/src/printing.c',
  c_deps_dir + '/submodules/ctable/src/vector.c',
  ]  
ctable_lib = library('ctable',
  ctable_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
ctable_dep = declare_dependency(include_directories: [inc], link_with: ctable_lib)
