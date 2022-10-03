miniaudio_srcs = [files(
  '../../../submodules/miniaudio/miniaudio.h',
  '../../../submodules/miniaudio/extras/miniaudio_split/miniaudio.c',
)]

miniaudio_dirs = [
  '../../../submodules/miniaudio',
  inc,
]

miniaudio_c_args = [
  '-Wno-unused-function',
  ]
miniaudio_deps = [

]

miniaudio_lib =library('miniaudio',
  miniaudio_srcs,
  install: false,
  dependencies: miniaudio_deps,
  include_directories: miniaudio_dirs,
  c_args: miniaudio_c_args,
)

miniaudio_dep = declare_dependency(
  include_directories: miniaudio_dirs,
  link_with: miniaudio_lib,
)
