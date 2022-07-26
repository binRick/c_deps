termbox2_srcs = [files(
  '../../../submodules/termbox2/termbox.h',
)]

termbox2_dirs = [
  '../../../submodules/termbox2',
  inc,
]

termbox2_deps = [

]

termbox2_lib = shared_library('termbox2',
  termbox2_srcs,
  install: false,
  dependencies: termbox2_deps,
  include_directories: termbox2_dirs,
)

termbox2_dep = declare_dependency(
  include_directories: termbox2_dirs,
  link_with: termbox2_lib,
)
