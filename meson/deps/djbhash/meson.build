
djbhash_dir =  'submodules/djbhash'
djbhash_srcs = [
  c_deps_dir + '/' + djbhash_dir + '/src/djbhash.c',
]
djbhash_cargs = [
  '-Wno-pointer-sign',
  '-Wno-return-type',
  '-Wno-varargs',
  '-Wno-unused-value',
  '-Wno-pragma-once-outside-header',
  '-Wno-unused-variable',
  '-Wno-sign-compare',
  ]
djbhash_inc = [
  inc,
]
djbhash_lib =library('djbhash', djbhash_srcs,
  install: false, 
  c_args: djbhash_cargs,
  dependencies: [
  ], 
  include_directories: djbhash_inc,
)
djbhash_dep = declare_dependency(
  include_directories: djbhash_inc,
  link_with: djbhash_lib,
)
