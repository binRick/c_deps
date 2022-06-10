libmutotp_lib = static_library('libmutotp',
  pwd + '/submodules/libmutotp/totp.c',
  pwd + '/submodules/libmutotp/sha1.c',
  pwd + '/submodules/libmutotp/base32codec.c',
  pwd + '/submodules/libmutotp/qrcode/qrcode.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    inc,
  ]
)
libmutotp_dep = declare_dependency(include_directories: [inc], link_with: libmutotp_lib)
