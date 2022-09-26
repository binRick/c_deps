c_binaries = [
  'hello',
  'adder',
  ]

foreach c : c_binaries 
  run_command('make','-B', '-C', meson.current_source_dir(), c, check: true)
  executable(c,
       'c-'+c+'/'+c+'.c',
       dependencies: [],
       include_directories: [
         'go-'+c,
         inc,
         ],
       link_args: [
         ],
       c_args: [
         ],
       objects: ['go-'+c+'/lib'+c+'.a'],
  )
endforeach

ui_dirs = ['c-ui','go-ui','.','../c-go-interface']
ui_objects = ['go-ui/libui.a']
ui_lib = library('ui',
  ['c-ui/ui.c'],
  install: false,
  dependencies: [],
  include_directories: ui_dirs,
  link_with: [],
  #link_whole: ui_objects,
  )

ui_dep = declare_dependency(
  include_directories: ui_dirs,
  link_with: [ui_lib],
  )
  
