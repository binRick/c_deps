bench_srcs = [files(
  '../../../submodules/c_bench/bench.c',
  '../../../submodules/c_bench/bench.h',

)]

bench_dirs = [
  '../../../submodules/c_bench',
  inc,
]

bench_deps = [

]

bench_lib = both_libraries('bench',
  bench_srcs,
  install: false,
  dependencies: bench_deps,
  include_directories: bench_dirs,
)

bench_dep = declare_dependency(
  include_directories: bench_dirs,
  link_with: bench_lib,
)
