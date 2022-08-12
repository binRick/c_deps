font_srcs = [files(
  '../../../submodules/font/font.h',
  '../../../submodules/font/font.c',
  '../../../submodules/font/lib.c',
)]

font_dirs = [
  '../../../submodules/font',
  inc,
]

font_deps = [

]

font_lib = library('font',
  font_srcs,
  install: false,
  dependencies: font_deps,
  include_directories: font_dirs,
)

font_dep = declare_dependency(
  include_directories: font_dirs,
  link_with: font_lib,
)
