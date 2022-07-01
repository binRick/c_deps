tuibox_srcs = [files(
)]

tuibox_dirs = [
  '../../../submodules/tuibox',
  inc,
]

tuibox_deps = [

]

tuibox_lib = shared_library('tuibox',
  tuibox_srcs,
  install: false,
  dependencies: tuibox_deps,
  include_directories: tuibox_dirs,
)

tuibox_dep = declare_dependency(
  include_directories: tuibox_dirs,
  link_with: tuibox_lib,
)
