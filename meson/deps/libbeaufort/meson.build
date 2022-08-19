libbeaufort_srcs = [
  '../../../submodules/libbeaufort/src/encrypt.c',
  '../../../submodules/libbeaufort/src/decrypt.c',
  '../../../submodules/libbeaufort/src/tableau.c',
]
libbeaufort_inc = [
  '../../../submodules/libbeaufort/src',
  '../../../submodules/libbeaufort/include',
  '../../../submodules/libbeaufort',
  inc,
]
libbeaufort_lib = static_library('libbeaufort', 
  libbeaufort_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: libbeaufort_inc,
)
libbeaufort_dep = declare_dependency(
  include_directories: libbeaufort_inc,
  link_with: libbeaufort_lib,
)
