
djbhash_dir =  'submodules/djbhash'
djbhash_srcs = [
  meson_deps_dir + '/' + djbhash_dir + '/src/djbhash.c',
]
djbhash_inc = [
  inc,
]
djbhash_lib = static_library('djbhash', djbhash_srcs,
  install: false, 
  dependencies: [
  ], 
  include_directories: djbhash_inc,
)
djbhash_dep = declare_dependency(
  include_directories: djbhash_inc,
  link_with: djbhash_lib,
)
