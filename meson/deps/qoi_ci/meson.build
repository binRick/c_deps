qoi_ci_system_headers = [

]
qoi_ci_local_headers = [
  'qoi_ci/QOI-stdio.h',
  'qoi_ci/transpiled/QOI.h',
]
qoi_ci_srcs = [
  '../../../submodules/qoi_ci/macos/qlqoi.c',
  '../../../submodules/qoi_ci/QOI-stdio.c',
  '../../../submodules/qoi_ci/transpiled/QOI.c',
]

qoi_ci_dirs = [
  '../../../submodules/qoi_ci/transpiled',
  '../../../submodules/qoi_ci',
  '../../../submodules/qoi_ci/macos',
]

qoi_ci_c_args = [
  '-Wno-unused-parameter',
  '-Wno-sign-compare',
]

qoi_ci_link_args = [
osx_ldflags,
  ]
qoi_ci_deps = [

]

if qoi_ci_srcs.length() > 0
  qoi_ci_lib = library('qoi_ci',
    files(qoi_ci_srcs),
    install: false,
    dependencies: qoi_ci_deps,
    include_directories: qoi_ci_dirs,
    c_args: qoi_ci_c_args,
  )
  qoi_ci_links = [qoi_ci_lib]
else
  qoi_ci_links = []
endif

qoi_ci_dep = declare_dependency(
  include_directories: qoi_ci_dirs,
  link_with: qoi_ci_links,
  link_args: qoi_ci_link_args,
)
