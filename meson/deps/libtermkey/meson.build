libtermkey_srcs = [
  '../../../submodules/libtermkey/driver-csi.c',
  '../../../submodules/libtermkey/driver-ti.c',
  '../../../submodules/libtermkey/driver-ti.c',
  '../../../submodules/libtermkey/termkey.c',
]

libtermkey_dirs = [
  '../../../submodules',
  '../../../submodules/libtermkey',
  inc,
]

libtermkey_deps = [

]

libtermkey_lib = library('libtermkey-lib',
  libtermkey_srcs,
  install: false,
  dependencies: libtermkey_deps,
  c_args: [ 
    ],
  link_args: [ 
    '-lcurses',
  ],
  include_directories: libtermkey_dirs,
)

libtermkey_dep = declare_dependency(
  include_directories: libtermkey_dirs,
  link_with: libtermkey_lib,
)
