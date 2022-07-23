libusb_srcs = [files(
  '../../../submodules/libusb/Xcode/config.h',
  '../../../submodules/libusb/libusb/core.c',
  '../../../submodules/libusb/libusb/descriptor.c',
  '../../../submodules/libusb/libusb/hotplug.c',
  '../../../submodules/libusb/libusb/io.c',
  '../../../submodules/libusb/libusb/libusb.h',
  '../../../submodules/libusb/libusb/libusbi.h',
  '../../../submodules/libusb/libusb/os/darwin_usb.c',
  '../../../submodules/libusb/libusb/os/darwin_usb.h',
  '../../../submodules/libusb/libusb/os/events_posix.c',
  '../../../submodules/libusb/libusb/os/events_posix.h',
  '../../../submodules/libusb/libusb/os/haiku_usb.h',
  '../../../submodules/libusb/libusb/os/haiku_usb_raw.h',
  '../../../submodules/libusb/libusb/os/threads_posix.c',
  '../../../submodules/libusb/libusb/os/threads_posix.h',
  '../../../submodules/libusb/libusb/strerror.c',
  '../../../submodules/libusb/libusb/sync.c',
  '../../../submodules/libusb/libusb/version.h',
  '../../../submodules/libusb/libusb/version_nano.h',
)]

libusb_dirs = [
  '../../../submodules/libusb',
  '../../../submodules/libusb/libusb',
  '../../../submodules/libusb/Xcode',
  '../../../submodules/libusb/libusb/os',
  inc,
]

libusb_deps = [

]

libusb_lib = shared_library('libusb',
  libusb_srcs,
  install: false,
  dependencies: libusb_deps,
  include_directories: libusb_dirs,
)

libusb_dep = declare_dependency(
  include_directories: libusb_dirs,
  link_with: libusb_lib,
)
