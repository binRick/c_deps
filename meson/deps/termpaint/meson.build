termpaint_dep = dependency('termpaint', required: true)
termpaint_image_dep = dependency('termpaint_image', required: true)
termpaint_srcs = [files(
  '../../../submodules/termpaint/ttyrescue.c',
  '../../../submodules/termpaint/termpaint.c',
  '../../../submodules/termpaint/termpaintx.c',
  '../../../submodules/termpaint/termpaintx.h',
  '../../../submodules/termpaint/termpaintx_ttyrescue.c',
  '../../../submodules/termpaint/termpaintx_ttyrescue.h',
  '../../../submodules/termpaint/termpaint_event.c',
  '../../../submodules/termpaint/termpaint_input.c',
  )]

termpaint_dirs = [
  '../../../submodules/termpaint',
  inc,
]

termpaint_deps = [

]

#termpaint_lib = shared_library('termpaint',
#  termpaint_srcs,
#  install: false,
#  dependencies: termpaint_deps,
#  c_args: [
#    '-DTERMPAINT_RESCUE_PATH="/tmp"',
#    '-DTERMPAINT_EXPORT_SYMBOLS',
#    ],
#  include_directories: termpaint_dirs,
#)

#termpaint_dep = declare_dependency(
#  include_directories: termpaint_dirs,
#  link_with: [termpaint_lib,termpaint_image_lib],
#)
