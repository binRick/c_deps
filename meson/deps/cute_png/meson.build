cute_png_srcs = [files(
  '../../../submodules/cute_headers/cute_png.h',
)]

cute_png_dirs = [
  '../../../submodules/cute_headers',
  inc,
]

cute_png_deps = [

]

cute_png_lib = both_libraries('cute-png',
  cute_png_srcs,
  install: false,
  dependencies: cute_png_deps,
  include_directories: cute_png_dirs,
)

cute_png_dep = declare_dependency(
  include_directories: cute_png_dirs,
  link_with: cute_png_lib,
)
