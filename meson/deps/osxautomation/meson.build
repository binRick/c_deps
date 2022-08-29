osxautomation_srcs = [files(
  '../../../submodules/osxautomation/osxautomation.c',
)]

osxautomation_dirs = [
  '../../../submodules/osxautomation',
  inc,
]

osxautomation_deps = [

]
osxautomation_link_args = ['-Wl,-framework,CoreFoundation','-Wl,-framework,Carbon','-Wl,-framework,Foundation', '-Wl,-framework,AppKit']
osxautomation_lib = static_library('osxautomation',
  osxautomation_srcs,
  install: false,
  dependencies: osxautomation_deps,
  link_args: osxautomation_link_args,
  include_directories: osxautomation_dirs,
)

osxautomation_dep = declare_dependency(
  include_directories: osxautomation_dirs,
  link_with: osxautomation_lib,
)
