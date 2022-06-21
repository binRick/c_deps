libmutotp_c_args = [
  '-Wno-format-security',
]
libmutotp_srcs = [
  meson_deps_dir + '/submodules/libmutotp/totp.c',
  meson_deps_dir + '/submodules/libmutotp/sha1.c',
  meson_deps_dir + '/submodules/libmutotp/base32codec.c',
  meson_deps_dir + '/submodules/libmutotp/qrcode/qrcode.c',
]  

libmutotp_lib = static_library('libmutotp',
  libmutotp_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
  ],
  c_args: libmutotp_c_args,
)
libmutotp_dep = declare_dependency(
  include_directories: [
    inc,
  ], 
  link_with: libmutotp_lib,
)
