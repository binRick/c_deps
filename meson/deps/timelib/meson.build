timelib_srcs = [files(
  '../../../submodules/timelib/astro.c',
  '../../../submodules/timelib/dow.c',
  '../../../submodules/timelib/interval.c',
  '../../../submodules/timelib/parse_date.c',
  '../../../submodules/timelib/parse_iso_intervals.c',
  '../../../submodules/timelib/parse_posix.c',
  '../../../submodules/timelib/parse_tz.c',
  '../../../submodules/timelib/timelib.c',
  '../../../submodules/timelib/tm2unixtime.c',
  '../../../submodules/timelib/unixtime2tm.c',
)]

timelib_dirs = [
  '../../../submodules/timelib',
  '../../../submodules/timelib/zones',
  inc,
]
timelib_c_args = [
  '-Wno-unused-parameter',
  ]
timelib_deps = [

]

timelib_lib =library('timelib',
  timelib_srcs,
  install: false,
  dependencies: timelib_deps,
  include_directories: timelib_dirs,
  c_args: timelib_c_args,
)

timelib_dep = declare_dependency(
  include_directories: timelib_dirs,
  link_with: timelib_lib,
)
