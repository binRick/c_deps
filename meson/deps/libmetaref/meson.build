libmetaref_srcs = [

]

libmetaref_dirs = [
  '../../../submodules/libmetaref',
  '../../../submodules/libmetaref/include',
  '../../../submodules/libmetaref/include/exotic',
  inc,
]

libmetaref_deps = [

]
if libmetaref_srcs.length() > 0

  libmetaref_lib =library('libmetaref',
    files(libmetaref_srcs),
    install: false,
    dependencies: libmetaref_deps,
    include_directories: libmetaref_dirs,
  )
  libmetaref_links = [libmetaref_lib]
else
  libmetaref_links = []
endif

libmetaref_dep = declare_dependency(
  include_directories: libmetaref_dirs,
  link_with: libmetaref_links,
)
