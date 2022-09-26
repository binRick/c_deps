libterminput_srcs = [files(
  '../../../submodules/libterminput/libterminput.c',
  '../../../submodules/libterminput/libterminput.h',
)]

libterminput_dirs = [
  '../../../submodules/libterminput',
  inc,
]

libterminput_deps = [

]

libterminput_lib =library('libterminput',
  libterminput_srcs,
  install: false,
  dependencies: libterminput_deps,
  include_directories: libterminput_dirs,
)

libterminput_dep = declare_dependency(
  include_directories: libterminput_dirs,
  link_with: libterminput_lib,
)
