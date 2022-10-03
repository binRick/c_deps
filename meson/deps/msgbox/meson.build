msgbox_srcs = [files(
  '../../../submodules/msgbox/cstructs/array.c',
  '../../../submodules/msgbox/cstructs/list.c',
  '../../../submodules/msgbox/cstructs/map.c',
  '../../../submodules/msgbox/cstructs/memprofile.c',
  '../../../submodules/msgbox/msgbox/msgbox.c',
)]
msgbox_c_args = [
  '-Wno-sign-compare',
  ]
msgbox_dirs = [
  '../../../submodules/msgbox',
  '../../../submodules/msgbox/cstructs',
  '../../../submodules/msgbox/msgbox',
  '../../../submodules/msgbox/out',
  inc,
]

msgbox_deps = [

]

msgbox_lib =library('msgbox',
  msgbox_srcs,
  install: false,
  dependencies: msgbox_deps,
  include_directories: msgbox_dirs,
  c_args: msgbox_c_args,
)

msgbox_dep = declare_dependency(
  include_directories: msgbox_dirs,
  link_with: msgbox_lib,
)
