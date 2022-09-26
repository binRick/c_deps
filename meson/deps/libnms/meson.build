libnms_srcs = [files(
  '../../../submodules/libnms/src/libnms.c',
)]

libnms_dirs = [
  '../../../submodules/libnms',
  '../../../submodules/libnms/src',
  inc,
]

libnms_deps = [

]

libnms_lib =library('libnms',
  libnms_srcs,
  install: false,
  dependencies: libnms_deps,
  include_directories: libnms_dirs,
)

libnms_dep = declare_dependency(
  include_directories: libnms_dirs,
  link_with: libnms_lib,
)
