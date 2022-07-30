smaz_srcs = [
  meson_deps_dir + '/submodules/smaz/smaz.c',
]  
smaz_lib = static_library('smaz', 
  smaz_srcs,
  install: false, 
  dependencies: [], 
  include_directories: [
    inc,
  ]
)
smaz_dep = declare_dependency(
  include_directories: [
    inc,
  ], 
  link_with: smaz_lib,
)
