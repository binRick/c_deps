cargs_dep = dependency('cargs',fallback:['cargs', 'cargs_dep'])

_cargs_lib = static_library('cargs', 
  '../../../submodules/cargs/src/cargs.c',
  install: false, 
  dependencies: [],
  include_directories: [
    '../../../submodules/cargs/include',
  ],
)
_cargs_dep = declare_dependency(
  include_directories: [],
  link_with: _cargs_lib,
)
