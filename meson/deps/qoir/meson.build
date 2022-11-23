qoir_system_headers = [

]
qoir_local_headers = [
  'qoir/src/qoir.h',
]
qoir_srcs = [
  '../../../submodules/qoir/util/pixbufs_are_equal.c',
  '../../../submodules/qoir/util/load_file.c',
]

qoir_dirs = [
  '../../../submodules/qoir',
  '../../../submodules/qoir/adapter',
  '../../../submodules/qoir/src',
  '../../../submodules/qoir/util',
  inc,
]

qoir_c_args = [
]

qoir_deps = [

]

if qoir_srcs.length() > 0
  qoir_lib_static = static_library('qoir',
    files(qoir_srcs),
    install: false,
    dependencies: qoir_deps,
    include_directories: qoir_dirs,
    c_args: qoir_c_args,
  )
  qoir_lib = library('qoir',
    files(qoir_srcs),
    install: false,
    dependencies: qoir_deps,
    include_directories: qoir_dirs,
    c_args: qoir_c_args,
  )
  qoir_links = [qoir_lib]
else
  qoir_links = []
endif

qoir_dep = declare_dependency(
  include_directories: qoir_dirs,
  link_with: qoir_links,
)
