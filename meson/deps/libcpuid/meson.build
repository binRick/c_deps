libcpuid_srcs = [files(
  '../../../submodules/libcpuid/contrib/MSR Driver/Kernel/TmpRdr.c',
  '../../../submodules/libcpuid/cpuid_tool/cpuid_tool.c',
  '../../../submodules/libcpuid/libcpuid/asm-bits.c',
  '../../../submodules/libcpuid/libcpuid/cpuid_main.c',
  '../../../submodules/libcpuid/libcpuid/libcpuid_util.c',
  '../../../submodules/libcpuid/libcpuid/msrdriver.c',
  '../../../submodules/libcpuid/libcpuid/rdmsr.c',
  '../../../submodules/libcpuid/libcpuid/rdtsc.c',
  '../../../submodules/libcpuid/libcpuid/recog_amd.c',
  '../../../submodules/libcpuid/libcpuid/recog_intel.c',
)]

libcpuid_dirs = [
  '../../../submodules/libcpuid',
  '../../../submodules/libcpuid/contrib',
  '../../../submodules/libcpuid/contrib/MSR Driver',
  '../../../submodules/libcpuid/contrib/MSR Driver/Kernel',
  '../../../submodules/libcpuid/cpuid_tool',
  '../../../submodules/libcpuid/debian',
  '../../../submodules/libcpuid/debian/source',
  '../../../submodules/libcpuid/libcpuid',
  inc,
]

libcpuid_deps = [

]

libcpuid_lib =library('libcpuid',
  libcpuid_srcs,
  install: false,
  dependencies: libcpuid_deps,
  c_args:[
    '-DVERSION="0.0.5"',
    ],
  include_directories: libcpuid_dirs,
)

libcpuid_dep = declare_dependency(
  include_directories: libcpuid_dirs,
  link_with: libcpuid_lib,
)
