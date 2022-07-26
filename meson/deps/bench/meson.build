bench_srcs = [files(
  '../../../submodules/bench/bench.c',
  '../../../submodules/bench/bench.h',

)]

bench_dirs = [
  '../../../submodules/bench',
  inc,
]

bench_deps = [

]

bench_lib = shared_library('bench',
  bench_srcs,
  install: false,
  dependencies: bench_deps,
  include_directories: bench_dirs,
)

bench_dep = declare_dependency(
  include_directories: bench_dirs,
  link_with: bench_lib,
)
