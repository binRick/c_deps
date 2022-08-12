bitfield_srcs = [files(
  '../../../submodules/bitfield/bitfield.c',
  '../../../submodules/bitfield/bitfield.h',
)]

bitfield_dirs = [
  '../../../submodules/bitfield',
  inc,
]

bitfield_deps = [

]

bitfield_lib = library('bitfield',
  bitfield_srcs,
  install: false,
  dependencies: bitfield_deps,
  include_directories: bitfield_dirs,
)

bitfield_dep = declare_dependency(
  include_directories: bitfield_dirs,
  link_with: bitfield_lib,
)
