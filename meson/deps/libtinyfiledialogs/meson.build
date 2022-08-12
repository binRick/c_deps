libtinyfiledialogs_srcs = [files(
  '../../../submodules/libtinyfiledialogs/tinyfiledialogs.c',
  '../../../submodules/libtinyfiledialogs/tinyfiledialogs.h',
)]

libtinyfiledialogs_dirs = [
  '../../../submodules/libtinyfiledialogs',
  inc,
]

libtinyfiledialogs_deps = [

]

libtinyfiledialogs_lib = library('libtinyfiledialogs',
  libtinyfiledialogs_srcs,
  install: false,
  dependencies: libtinyfiledialogs_deps,
  include_directories: libtinyfiledialogs_dirs,
)

libtinyfiledialogs_dep = declare_dependency(
  include_directories: libtinyfiledialogs_dirs,
  link_with: libtinyfiledialogs_lib,
)
