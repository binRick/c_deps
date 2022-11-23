c_fzf_system_headers = [

]
c_fzf_local_headers = [
  'c_fzf/fzf/fzf.h',
]
c_fzf_srcs = [
  '../../../submodules/c_fzf/fzf/fzf.c',
]

c_fzf_dirs = [
  '../../../submodules/c_fzf',
  '../../../submodules/c_fzf/fzf',
  inc,
]

c_fzf_c_args = [
]

c_fzf_deps = [
  c_vector_dep,reproc_dep,which_dep,tempdir_dep,c_string_buffer_dep,
  c_fsio_dep,
  c_stringfn_dep,timestamp_dep,

]

if c_fzf_srcs.length() > 0
  c_fzf_lib = library('c_fzf',
    files(c_fzf_srcs),
    install: false,
    dependencies: c_fzf_deps,
    include_directories: c_fzf_dirs,
    c_args: c_fzf_c_args,
  )
  c_fzf_links = [c_fzf_lib]
else
  c_fzf_links = []
endif

c_fzf_dep = declare_dependency(
  include_directories: c_fzf_dirs,
  link_with: c_fzf_links,
)
