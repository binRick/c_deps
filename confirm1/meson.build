#  project('confirm1',['c','cpp'],default_options:['warning_level=0','c_std=gnu99'])
#############################################################
#  go_program = find_program('go', required : true)
#  gofmt_program = find_program('gofmt', required : true)
#  goimports_program = find_program('goimports', required : true)
#  fs = import('fs')
#  cc = meson.get_compiler('c', native: true)
#  cpp = meson.get_compiler('cpp', native: true)
#  c_deps_dir = meson.current_source_dir()
#endif

go_name = 'confirm1'
go_files = [
  go_name + '.go',
]
confirm1_srcs = [
  go_name + '.c',
  go_name + '.h',
]
confirm1_objects = [
  go_name + '.a',
]
confirm1_dirs = [
  '.',
]
confirm1_deps = []
confirm1_link_args = []
confirm1_c_args = []

run_command(gofmt_program, '-w', go_files, check: true)
run_command(goimports_program, '-w', go_files, check: true)
if not fs.is_file('go.mod')
  run_command(go_program, 'mod', 'init', go_name, check: true)
endif
run_command(go_program, 'mod', 'tidy', check: true)
run_command(go_program, 'build', '-o', go_name + '.a', '-buildmode=c-archive', go_files, check: true)

confirm1 = executable(go_name,
     confirm1_srcs,
     dependencies: confirm1_deps,
     include_directories: confirm1_dirs,
     link_args: confirm1_link_args,
     c_args: confirm1_c_args,
     objects: confirm1_objects,
     install: true,
)

