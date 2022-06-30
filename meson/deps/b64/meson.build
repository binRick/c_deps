b64_srcs = [
  '../../../submodules/b64.c/decode.c',
  '../../../submodules/b64.c/encode.c',
  '../../../submodules/b64.c/buffer.c',
]
b64_dirs = [
    '../../../submodules/b64.c',
    inc,
  ]
b64_lib = shared_library('b64', b64_srcs,
  install: false, dependencies: [
  ], 
  include_directories: b64_dirs,
)
b64_dep = declare_dependency(include_directories: b64_dirs, link_with: b64_lib)
