movewin_srcs = [files(
  '../../../submodules/movewin/winutils.c',
)]

movewin_dirs = [
  '../../../submodules/movewin',
  inc,
]

movewin_deps = [

]

movewin_lib = static_library('movewin',
  movewin_srcs,
  install: false,
  dependencies: movewin_deps,
  include_directories: movewin_dirs,
)

movewin_dep = declare_dependency(
  include_directories: movewin_dirs,
  link_with: movewin_lib,
)
