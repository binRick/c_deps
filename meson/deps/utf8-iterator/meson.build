utf8_iterator_srcs = [files(
  '../../../submodules/utf8-iterator/source/utf-8.c',
  '../../../submodules/utf8-iterator/source/utf-8.h',
)]

utf8_iterator_dirs = [
  '../../../submodules/utf8-iterator',
  inc,
]

utf8_iterator_deps = [

]

utf8_iterator_lib = static_library('utf8-iterator',
  utf8_iterator_srcs,
  install: false,
  dependencies: utf8_iterator_deps,
  include_directories: utf8_iterator_dirs,
)

utf8_iterator_dep = declare_dependency(
  include_directories: utf8_iterator_dirs,
  link_with: utf8_iterator_lib,
)
