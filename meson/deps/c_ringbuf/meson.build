c_ringbuf_system_headers = [

]
c_ringbuf_local_headers = [
  'c_ringbuf/ringbuf.h',
]
c_ringbuf_srcs = [
  '../../../submodules/c_ringbuf/ringbuf.c',
]

c_ringbuf_dirs = [
  '../../../submodules/c_ringbuf',
  inc,
]

c_ringbuf_c_args = [
]

c_ringbuf_deps = [

]

if c_ringbuf_srcs.length() > 0
  c_ringbuf_lib = library('c_ringbuf',
    files(c_ringbuf_srcs),
    install: false,
    dependencies: c_ringbuf_deps,
    include_directories: c_ringbuf_dirs,
    c_args: c_ringbuf_c_args,
  )
  c_ringbuf_links = [c_ringbuf_lib]
else
  c_ringbuf_links = []
endif

c_ringbuf_dep = declare_dependency(
  include_directories: c_ringbuf_dirs,
  link_with: c_ringbuf_links,
)
