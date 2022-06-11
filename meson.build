project('meson_deps', ['c'],
  default_options: [
   'warning_level=0',
   'c_std=gnu99',
  ]
)
#############################################################
cc = meson.get_compiler('c')
#//***********************************************************/
osx_ldflags = []
deps = []
bin_srcs = []
submodule_srcs = []
#############################################################
fs = import('fs')
pkg_config = import('pkgconfig')
#############################################################
config = configuration_data()
version = run_command('git', 'describe', '--tags')
config.set('version', version.stdout().strip())
add_project_arguments('-D_GNU_SOURCE', language : 'c')
add_project_arguments('-DDBG_H_DEF_ONCE', language : 'c')
add_project_arguments('-DDBG_H_NO_WARNING', language : 'c')
add_project_arguments('-DASSERTF_DEF_ONCE', language : 'c')
add_project_arguments('-DLOG_USE_COLOR', language : 'c')
add_project_arguments('-DLOG_LEVEL=TRACE', language : 'c')
add_project_arguments('-Wno-pragma-once-outside-header', language : 'c')
add_project_arguments('-Wno-incompatible-pointer-types', language : 'c')
add_project_arguments('-Wno-pointer-sign', language : 'c')
add_project_arguments('-Wno-unused-value', language : 'c')
add_project_arguments('-Wno-gnu-alignof-expression', language : 'c')
add_project_arguments('-Wno-varargs', language : 'c')
add_project_arguments('-Wno-return-type', language : 'c')
#############################################################################
#osx_ldflags += ['-Wl,-framework,CoreFoundation']
#osx_ldflags += '-Wl,-framework,Carbon'
#osx_ldflags += ['-Wl,-framework,Foundation', '-Wl,-framework,AppKit']
#add_project_link_arguments(osx_ldflags, language : ['objc', 'c'])
pwd_bin = find_program('pwd', required : true)
pwd = run_command(pwd_bin, check: true).stdout().strip()
meson_deps_dir = pwd
#############################################################################
inc = [
  include_directories('submodules/libspng/spng'),
  include_directories('submodules/debug_print_h'),
  include_directories('submodules/debug_print_h/src'),
  include_directories('submodules'),
  include_directories('submodules/c_fsio/include'),
  include_directories('submodules/c_string_buffer/include'),
  include_directories('submodules/c_stringfn/include'),
  include_directories('submodules/djbhash/src'),
  #  include_directories('submodules/incbin'),
  include_directories('submodules/greatest'),
  include_directories('submodules/debug_print_h/src'),
  include_directories('submodules/debug_print_h/include'),
  include_directories('submodules/progressbar/include/progressbar'),
  include_directories('submodules/fs.c'),
  include_directories('submodules/slug.c/deps'),
  include_directories('submodules/which/src'),
  include_directories('submodules/str-ends-with'),
  include_directories('.'),
]  
###########################################
subdir('meson')
###########################################
subdir('deps')
subdir('deps-test')
###########################################
subdir('term-tests')
subdir('term-tests-test')
###########################################
subdir('ctable')
subdir('tests-table')
###########################################
