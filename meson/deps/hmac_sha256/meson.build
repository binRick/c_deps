hmac_sha256_srcs = [files(
  '../../../submodules/hmac_sha256/hmac-sha256.c',
)]

hmac_sha256_dirs = [
  '../../../submodules/hmac_sha256',
  inc,
]

hmac_sha256_deps = [

]

hmac_sha256_lib =library('hmac_sha256',
  hmac_sha256_srcs,
  install: false,
  dependencies: hmac_sha256_deps,
  include_directories: hmac_sha256_dirs,
)

hmac_sha256_dep = declare_dependency(
  include_directories: hmac_sha256_dirs,
  link_with: hmac_sha256_lib,
)
