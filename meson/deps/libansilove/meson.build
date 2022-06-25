libansilove_srcs = [
  '../../../submodules/libansilove/src/clean.c',
  '../../../submodules/libansilove/src/drawchar.c',
  '../../../submodules/libansilove/src/error.c',
  '../../../submodules/libansilove/src/fonts.c',
  '../../../submodules/libansilove/src/init.c',
  '../../../submodules/libansilove/src/loadfile.c',
  '../../../submodules/libansilove/src/output.c',
  '../../../submodules/libansilove/src/savefile.c',
  '../../../submodules/libansilove/src/loaders/ansi.c',
  '../../../submodules/libansilove/src/loaders/artworx.c',
  '../../../submodules/libansilove/src/loaders/binary.c',
  '../../../submodules/libansilove/src/loaders/icedraw.c',
  '../../../submodules/libansilove/src/loaders/pcboard.c',
  '../../../submodules/libansilove/src/loaders/tundra.c',
  '../../../submodules/libansilove/src/loaders/xbin.c',
  '../../../submodules/libansilove/compat/strtonum.c',
  '../../../submodules/libansilove/compat/reallocarray.c',
]
libansilove_lib = static_library('libansilove', 
  libansilove_srcs,
  install: false,
  dependencies: [
    gd_dep,
  ], 
  include_directories: [
    inc,
    '../../../submodules',
    '../../../submodules/libansilove/compat',
    '../../../submodules/libansilove/src',
    '../../../submodules/libansilove/include',
  ]
)

libansilove_dep = declare_dependency(
  include_directories: [
    inc,
    '../../../submodules/libansilove/compat',
    '../../../submodules/libansilove/include',
    '../../../submodules/libansilove/src',
  ], 
  link_with: libansilove_lib,
)
