wsServer_srcs = [files(
  '../../../submodules/wsServer/include/base64.h',
  '../../../submodules/wsServer/include/sha1.h',
  '../../../submodules/wsServer/include/utf8.h',
  '../../../submodules/wsServer/include/ws.h',
  '../../../submodules/wsServer/src/base64.c',
  '../../../submodules/wsServer/src/handshake.c',
  '../../../submodules/wsServer/src/sha1.c',
  '../../../submodules/wsServer/src/utf8.c',
  '../../../submodules/wsServer/src/ws.c',
)]

wsServer_dirs = [
  '../../../submodules/wsServer',
  '../../../submodules/wsServer/doc',
  '../../../submodules/wsServer/include',
  '../../../submodules/wsServer/src',
  inc,
]

wsServer_deps = [

]

wsServer_lib = static_library('wsServer',
  wsServer_srcs,
  install: false,
  dependencies: wsServer_deps,
  include_directories: wsServer_dirs,
)

wsServer_dep = declare_dependency(
  include_directories: wsServer_dirs,
  link_with: wsServer_lib,
)
