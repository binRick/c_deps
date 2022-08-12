levenshtein_srcs = [files(
  '../../../submodules/levenshtein/deps/levenshtein.c/levenshtein.c',
)]

levenshtein_dirs = [
  '../../../submodules/levenshtein',
  '../../../submodules/levenshtein/deps',
  inc,
]

levenshtein_deps = [

]

levenshtein_lib = both_libraries('levenshtein',
  levenshtein_srcs,
  install: false,
  dependencies: levenshtein_deps,
  include_directories: levenshtein_dirs,
)

levenshtein_dep = declare_dependency(
  include_directories: levenshtein_dirs,
  link_with: levenshtein_lib,
)
