exec_fzf_srcs = [
  'exec-fzf.c',
  'exec-fzf-effects.h',
]
exec_fzf_inc = [
 inc,
 '../exec-fzf',
 '../submodules/reproc/reproc/include',
 '../submodules/reproc/reproc/include/reproc',
 '../submodules/reproc/reproc',
 '../submodules/reproc',
]
exec_fzf_c_args = [
  '-Wno-unused-functions',
  '-Wno-unknown-warning-option',
  '-INCBIN_SILENCE_BITCODE_WARNING',
  ]
exec_fzf_deps = [
 reproc_dep,
 ansi_codes_dep,
 c_fsio_dep,
 module_dep,
 c_stringfn_dep,
 c_vector_dep,
 tempdir_dep,
 which_dep,
 timestamp_dep,
 ansi_utils_dep,
 bytes_dep,
 #debug_memory_dep,
 c_string_buffer_dep,
 b64_dep,
 log_dep,
]


exec_fzf_lib = library('exec-fzf',
  exec_fzf_srcs,
  install: false,
  dependencies: exec_fzf_deps,
  include_directories: exec_fzf_inc,
  c_args: exec_fzf_c_args,
)


exec_fzf_dep = declare_dependency(
  include_directories: exec_fzf_inc,
  link_with: exec_fzf_lib,
)
