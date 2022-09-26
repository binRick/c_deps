stb_srcs = [files(
  '../../../submodules/stb/stb_vorbis.c',
)]

stb_dirs = [
  '../../../submodules/stb',
  inc,
]

stb_deps = [

]

stb_lib =library('stb',
  stb_srcs,
  install: false,
  dependencies: stb_deps,
  include_directories: stb_dirs,
)

stb_dep = declare_dependency(
  include_directories: stb_dirs,
  link_with: stb_lib,
)
