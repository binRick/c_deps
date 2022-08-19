embedded_palettes_srcs = [
  c_deps_dir+'/submodules/c_palettes/embeds/tbl1.c',
]

embedded_palettes_lib = static_library('embedded_palettes', 
  embedded_palettes_srcs,
  install: false, 
  dependencies: [], 
  include_directories: [
    inc
  ]
)
embedded_palettes_dep = declare_dependency(
  include_directories: [
    inc
  ], 
  link_with: embedded_palettes_lib)
