colorwheel_srcs = [files(
  '../../../submodules/colorwheel/colorwheel.h',
)]

colorwheel_dirs = [
  '../../../submodules/colorwheel',
  inc,
]

colorwheel_deps = [

]

colorwheel_lib = shared_library('colorwheel',
  colorwheel_srcs,
  install: false,
  dependencies: colorwheel_deps,
  include_directories: colorwheel_dirs,
)

colorwheel_dep = declare_dependency(
  include_directories: colorwheel_dirs,
  link_with: colorwheel_lib,
)
