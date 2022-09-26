filecopy_srcs = [files(
  '../../../submodules/filecopy/filecopy.c',
)]

filecopy_dirs = [
  '../../../submodules/filecopy',
  inc,
]

filecopy_deps = [

]

filecopy_lib =library('filecopy',
  filecopy_srcs,
  install: false,
  dependencies: filecopy_deps,
  include_directories: filecopy_dirs,
)

filecopy_dep = declare_dependency(
  include_directories: filecopy_dirs,
  link_with: filecopy_lib,
)
