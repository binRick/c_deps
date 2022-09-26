c_dt_srcs = [files(
  '../../../submodules/c-dt/dt.h',
  '../../../submodules/c-dt/dt_accessor.c',
  '../../../submodules/c-dt/dt_accessor.h',
  '../../../submodules/c-dt/dt_arithmetic.c',
  '../../../submodules/c-dt/dt_arithmetic.h',
  '../../../submodules/c-dt/dt_char.c',
  '../../../submodules/c-dt/dt_char.h',
  '../../../submodules/c-dt/dt_config.h',
  '../../../submodules/c-dt/dt_core.c',
  '../../../submodules/c-dt/dt_core.h',
  '../../../submodules/c-dt/dt_dow.c',
  '../../../submodules/c-dt/dt_dow.h',
  '../../../submodules/c-dt/dt_easter.c',
  '../../../submodules/c-dt/dt_easter.h',
  '../../../submodules/c-dt/dt_length.c',
  '../../../submodules/c-dt/dt_length.h',
  '../../../submodules/c-dt/dt_navigate.c',
  '../../../submodules/c-dt/dt_navigate.h',
  '../../../submodules/c-dt/dt_parse_iso.c',
  '../../../submodules/c-dt/dt_parse_iso.h',
  '../../../submodules/c-dt/dt_search.c',
  '../../../submodules/c-dt/dt_search.h',
  '../../../submodules/c-dt/dt_tm.c',
  '../../../submodules/c-dt/dt_tm.h',
  '../../../submodules/c-dt/dt_util.c',
  '../../../submodules/c-dt/dt_util.h',
  '../../../submodules/c-dt/dt_valid.c',
  '../../../submodules/c-dt/dt_valid.h',
  '../../../submodules/c-dt/dt_weekday.c',
  '../../../submodules/c-dt/dt_weekday.h',
  '../../../submodules/c-dt/dt_workday.c',
  '../../../submodules/c-dt/dt_workday.h',
  '../../../submodules/c-dt/dt_zone.c',
  '../../../submodules/c-dt/dt_zone.h',
  '../../../submodules/c-dt/dt_zone_entries.h',
)]

c_dt_dirs = [
  '../../../submodules/c-dt',
  inc,
]

c_dt_deps = [

]

c_dt_lib =library('c-dt',
  c_dt_srcs,
  install: false,
  dependencies: c_dt_deps,
  include_directories: c_dt_dirs,
)

c_dt_dep = declare_dependency(
  include_directories: c_dt_dirs,
  link_with: c_dt_lib,
)
