b64_srcs = [
  pwd + '/submodules/b64.c/decode.c',
  pwd + '/submodules/b64.c/encode.c',
  pwd + '/submodules/b64.c/buffer.c',

]
b64_lib = static_library('b64', b64_srcs,
  install: false, dependencies: [
  ], 
  include_directories: [
    inc,
  ]
)
b64_dep = declare_dependency(include_directories: inc, link_with: b64_lib)
