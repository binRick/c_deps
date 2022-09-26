libconfuse_srcs = [files(
  '../../../submodules/libconfuse/src/reallocarray.c',
  '../../../submodules/libconfuse/src/lexer.c',
  '../../../submodules/libconfuse/src/confuse.c',
  '../../../submodules/libconfuse/config.h',
)]

libconfuse_dirs = [
  '../../../submodules/libconfuse',
  '../../../submodules/libconfuse/src',
  inc,
]

libconfuse_c_args = [
  '-DHAVE_CONFIG_H',
  '-DLOCALEDIR="/usr/local/share/locale"',
  '-DBUILDING_DLL',
  '-DPIC',
  ]
libconfuse_deps = [

]

#libconfuse_lib =library('libconfuse',
#  libconfuse_srcs,
#  install: false,
#  dependencies: libconfuse_deps,
#  c_args: libconfuse_c_args,
#  include_directories: libconfuse_dirs,
#)
libconfuse_dep = dependency('libconfuse', method: 'pkg-config', required: true)
_libconfuse_dep = declare_dependency(
  include_directories: libconfuse_dirs,
  link_with: [],
)
