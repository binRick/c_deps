fancy_progress_srcs = [files(
  '../../../submodules/fancy-progress/src/fancy-progress.c',
)]

fancy_progress_dirs = [
  '../../../submodules/fancy-progress',
  '../../../submodules/fancy-progress/src',
  inc,
]

fancy_progress_deps = [

]

fancy_progress_lib =library('fancy-progress',
  fancy_progress_srcs,
  install: false,
  dependencies: fancy_progress_deps,
  include_directories: fancy_progress_dirs,
)

fancy_progress_dep = declare_dependency(
  include_directories: fancy_progress_dirs,
  link_with: fancy_progress_lib,
)
