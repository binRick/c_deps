b64_srcs = [
  meson_deps_dir+'/submodules/b64.c/decode.c',
  meson_deps_dir+'/submodules/b64.c/encode.c',
  meson_deps_dir+'/submodules/b64.c/buffer.c',

]
b64_lib = static_library('b64', b64_srcs,
  install: false, dependencies: [
  ], 
  include_directories: [ inc,
  ]
)
b64_dep = declare_dependency(include_directories: [inc], link_with: b64_lib)
