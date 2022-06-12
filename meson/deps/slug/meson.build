slug_lib = static_library('slug',
  meson_deps_dir + '/submodules/slug.c/src/slug.c',
  meson_deps_dir + '/submodules/slug.c/deps/case.c',
  meson_deps_dir + '/submodules/slug.c/deps/trim.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
slug_dep = declare_dependency(include_directories: [inc], link_with: slug_lib)
