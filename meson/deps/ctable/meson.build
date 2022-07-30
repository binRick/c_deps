ctable_srcs = [
  meson_deps_dir + '/submodules/ctable/src/table.c',
  meson_deps_dir + '/submodules/ctable/src/constraint.c',
  meson_deps_dir + '/submodules/ctable/src/alloc_wrappers.c',
  meson_deps_dir + '/submodules/ctable/src/string_util.c',
  meson_deps_dir + '/submodules/ctable/src/printing.c',
  meson_deps_dir + '/submodules/ctable/src/vector.c',
  ]  
ctable_lib = static_library('ctable',
  ctable_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
ctable_dep = declare_dependency(include_directories: [inc], link_with: ctable_lib)
