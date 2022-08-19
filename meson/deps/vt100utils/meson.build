vt100utils_srcs = [files(
    '../../../submodules/c_vt100utils/vt100utils.c',
    '../../../submodules/c_vt100utils/tuibox.c',
    '../../../submodules/c_vt100utils/tuibox-vec.c',
)]

vt100utils_dirs = [
  '../../../submodules/c_vt100utils',
  inc,
]

vt100utils_cargs = [
  '-Wno-bugprone-sizeof-expression',

]
vt100utils_deps = [

]

vt100utils_lib = static_library('vt100utils',
  vt100utils_srcs,
  install: false,
  dependencies: vt100utils_deps,
  c_args: vt100utils_cargs,
  include_directories: vt100utils_dirs,
)

vt100utils_dep = declare_dependency(
  include_directories: vt100utils_dirs,
  link_with: [vt100utils_lib],
)
