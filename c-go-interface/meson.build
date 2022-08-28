c_binaries = [
  'hello',
  'adder'
  ]

foreach c : c_binaries 
  run_command('make','-B', '-C', meson.current_source_dir(), c, check: true)
  c_hello = executable(c,
       'c-'+c+'/'+c+'.c',
       dependencies: [
         ],
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
