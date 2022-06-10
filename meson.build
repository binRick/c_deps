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
osx_ldflags += ['-Wl,-framework,CoreFoundation']
osx_ldflags += '-Wl,-framework,Carbon'
osx_ldflags += ['-Wl,-framework,Foundation', '-Wl,-framework,AppKit']

pwd_bin = find_program('pwd', required : true)
pwd = run_command(pwd_bin, check: true).stdout().strip()
add_project_link_arguments(osx_ldflags, language : ['objc', 'c'])
#############################################################################
inc = [
  include_directories('submodules'),
  include_directories('submodules/c_fsio/include'),
  include_directories('submodules/c_string_buffer/include'),
  include_directories('submodules/c_stringfn/include'),
  include_directories('submodules/djbhash/src'),
  include_directories('.'),
]  
#//////////////////////////////////////////////////////////////////////
subdir('meson/deps/parson')
subdir('meson/deps/cargs')
subdir('meson/deps/greatest')
subdir('meson/deps/c_stringfn')
subdir('meson/deps/ansicodes')
subdir('meson/deps/bytes')
subdir('meson/deps/c_string_buffer')
subdir('meson/deps/djbhash')
subdir('meson/deps/fs')
subdir('meson/deps/asprintf')
subdir('meson/deps/assertf')
subdir('meson/deps/b64')
#subdir('meson/deps/c_colors')
#subdir('meson/deps/c_embed')
subdir('meson/deps/c_fsio')
subdir('meson/deps/c_timer')
subdir('meson/deps/cflag')
subdir('meson/deps/chan')
subdir('meson/deps/cstructs_json')
subdir('meson/deps/dbg')
subdir('meson/deps/debug-memory')
#subdir('meson/deps/debug_print_h')
#subdir('meson/deps/djbhash')
#subdir('meson/deps/embedded_palettes')
subdir('meson/deps/generic_print')
subdir('meson/deps/http-get')
subdir('meson/deps/incbin')
subdir('meson/deps/libyaml')
subdir('meson/deps/module')
subdir('meson/deps/ms')
subdir('meson/deps/occurrences')
#subdir('meson/deps/path-basename')
subdir('meson/deps/progress')
subdir('meson/deps/rgba')
subdir('meson/deps/smaz')
subdir('meson/deps/sqlite3')
#subdir('meson/deps/str-replace')
subdir('meson/deps/strdup')
#subdir('meson/deps/svpng')
subdir('meson/deps/tempdir')
subdir('meson/deps/termpaint')
subdir('meson/deps/timestamp')
#//////////////////////////////////////////////////////////////////////
subdir('deps')
subdir('deps-test')
#//////////////////////////////////////////////////////////////////////
