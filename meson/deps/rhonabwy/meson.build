rhonabwy_srcs = [files(
  '../../../submodules/rhonabwy/src/jwe.c',
  '../../../submodules/rhonabwy/src/jwk.c',
  '../../../submodules/rhonabwy/src/jwks.c',
  '../../../submodules/rhonabwy/src/jws.c',
  '../../../submodules/rhonabwy/src/jwt.c',
  '../../../submodules/rhonabwy/src/misc.c',
)]

rhonabwy_dirs = [
  '../../../submodules/rhonabwy',
  '../../../submodules/rhonabwy/include',
  '../../../submodules/rhonabwy/src',
  '../../../submodules/rhonabwy/orcania-src/include',
  '../../../submodules/rhonabwy/orcania-src/src',
  '../../../submodules/rhonabwy/orcania-build',
  '../../../submodules/rhonabwy/yder-src/include',
  inc,
]

rhonabwy_deps = [
  nettle_dep,
  jansson_dep,
  curl_dep,
  orcania_dep,
  yder_dep,
  deflate_dep,
  gnutls_dep,
  zlib_dep,
]

rhonabwy_lib = shared_library('rhonabwy',
  rhonabwy_srcs,
  install: false,
  dependencies: rhonabwy_deps,
  include_directories: rhonabwy_dirs,
)

rhonabwy_dep = declare_dependency(
  include_directories: rhonabwy_dirs,
  link_with: rhonabwy_lib,
)
