panic_srcs = [files(
  '../../../submodules/panic/sources/panic.c',
)]

panic_dirs = [
  '../../../submodules/panic',
  '../../../submodules/panic/sources',
  '../../../submodules/panic/deps',
  '../../../submodules/panic/deps/trace',
  inc,
]

panic_deps = [

]

panic_lib =library('panic',
  panic_srcs,
  install: false,
  dependencies: panic_deps,
  c_args: [
'-DPANIC_UNWIND_SUPPORT=1',
    ],
  include_directories: panic_dirs,
)

panic_dep = declare_dependency(
  include_directories: panic_dirs,
  link_with: panic_lib,
)
