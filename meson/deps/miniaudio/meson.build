miniaudio_srcs = [files(
  '../../../submodules/miniaudio/miniaudio.h',
  '../../../submodules/miniaudio/extras/miniaudio_split/miniaudio.c',
)]

miniaudio_dirs = [
  '../../../submodules/miniaudio',
  inc,
]

miniaudio_deps = [

]

miniaudio_lib = static_library('miniaudio',
  miniaudio_srcs,
  install: false,
  dependencies: miniaudio_deps,
  include_directories: miniaudio_dirs,
)

miniaudio_dep = declare_dependency(
  include_directories: miniaudio_dirs,
  link_with: miniaudio_lib,
)
