semver_c_srcs = [files(
  '../../../submodules/semver.c/semver.c',
  '../../../submodules/semver.c/semver.h',
  '../../../submodules/semver.c/semver_unit.c',
)]

semver_c_dirs = [
  '../../../submodules/semver.c',
  inc,
]

semver_c_deps = [

]

semver_c_lib = library('semver.c',
  semver_c_srcs,
  install: false,
  dependencies: semver_c_deps,
  include_directories: semver_c_dirs,
)

semver_c_dep = declare_dependency(
  include_directories: semver_c_dirs,
  link_with: semver_c_lib,
)
