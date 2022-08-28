occurrences_lib = static_library('occurrences',
  '../../../submodules/occurrences.c/occurrences.c',
  install: false, 
  dependencies: [
  ], 
  include_directories: [
    inc,
    '../../../submodules/occurrences.c',
  ]
)
occurrences_dep = declare_dependency(include_directories: 
  [
    inc,
    '../../../submodules/occurrences.c',
  ], 
  link_with: occurrences_lib
)
