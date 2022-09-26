hidapi_srcs = [files(
  '../../../submodules/hidapi/hidapi/hidapi.h',
  '../../../submodules/hidapi/mac/hid.c',
  '../../../submodules/hidapi/mac/hidapi_darwin.h',
)]

hidapi_dirs = [
  '../../../submodules/hidapi',
  '../../../submodules/hidapi/android',
  '../../../submodules/hidapi/android/jni',
  '../../../submodules/hidapi/dist',
  '../../../submodules/hidapi/hidapi',
  '../../../submodules/hidapi/libusb',
  '../../../submodules/hidapi/linux',
  '../../../submodules/hidapi/mac',
  '../../../submodules/hidapi/pc',
  '../../../submodules/hidapi/src',
  '../../../submodules/hidapi/udev',
  inc,
]

hidapi_deps = [

]

hidapi_lib =library('hidapi',
  hidapi_srcs,
  install: false,
  dependencies: hidapi_deps,
  include_directories: hidapi_dirs,
)

hidapi_dep = declare_dependency(
  include_directories: hidapi_dirs,
  link_with: hidapi_lib,
)
