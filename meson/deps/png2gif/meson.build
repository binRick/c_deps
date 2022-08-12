png2gif_srcs = [files(
  '../../../submodules/png2gif/pngReader.c',
)]

png2gif_dirs = [
  '../../../submodules/png2gif',
  inc,
]

png2gif_deps = [

]

png2gif_lib = library('png2gif',
  png2gif_srcs,
  install: false,
  dependencies: png2gif_deps,
  include_directories: png2gif_dirs,
)

png2gif_dep = declare_dependency(
  include_directories: png2gif_dirs,
  link_with: png2gif_lib,
)
