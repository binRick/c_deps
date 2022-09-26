libutf8_srcs = [files(
  '../../../submodules/libutf8/decode.c',
  '../../../submodules/libutf8/encode.c',
)]

libutf8_dirs = [
  '../../../submodules/libutf8',
  inc,
]

libutf8_deps = [

]

libutf8_lib =library('libutf8',
  libutf8_srcs,
  install: false,
  dependencies: libutf8_deps,
  include_directories: libutf8_dirs,
)

libutf8_dep = declare_dependency(
  include_directories: libutf8_dirs,
  link_with: libutf8_lib,
)
