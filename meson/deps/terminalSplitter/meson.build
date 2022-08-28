terminalSplitter_srcs = [files(
  '../../../submodules/terminalSplitter/Display.c',
)]

terminalSplitter_dirs = [
  '../../../submodules/terminalSplitter',
  inc,
]

terminalSplitter_deps = [

]

terminalSplitter_lib = static_library('terminalSplitter',
  terminalSplitter_srcs,
  install: false,
  dependencies: terminalSplitter_deps,
  include_directories: terminalSplitter_dirs,
)

terminalSplitter_dep = declare_dependency(
  include_directories: terminalSplitter_dirs,
  link_with: terminalSplitter_lib,
)
