occurrences_lib = library('c_string_buffer', 
  'submodules/meson_deps/submodules/occurences.c/occurrences.c',
  install: false, 
  dependencies: [], 
  include_directories: [inc,
  ]
)
occurrences_dep = declare_dependency(include_directories: 
  [inc,
    ], 
  link_with: occurrences_lib)
#deps += stringbuffer_dep
