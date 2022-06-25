libtermkey_srcs = [files(
  '../../../submodules/libtermkey/driver-csi.c',
  '../../../submodules/libtermkey/driver-ti.c',
  '../../../submodules/libtermkey/termkey-internal.h',
  '../../../submodules/libtermkey/termkey.c',
)]

libtermkey_dirs = [
  '../../../submodules/libtermkey',
  inc,
]

libtermkey_deps = [

]

libtermkey_lib = shared_library('libtermkey',
  libtermkey_srcs,
  install: false,
  dependencies: libtermkey_deps,
  include_directories: libtermkey_dirs,
)

libtermkey_dep = declare_dependency(
  include_directories: libtermkey_dirs,
  link_with: libtermkey_lib,
)
