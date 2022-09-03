osx_audit_flags = get_variable('osx_audit_flags', [])
osx_ldflags =     get_variable('osx_ldflags', [])
osx_wg_flags =     get_variable('osx_wgflags', [])
osx_img_flags =     get_variable('osx_imgflags', [])


osx_ldflags +=  ['-Wl,-framework,CoreFoundation']
osx_ldflags +=  ['-Wl,-framework,CoreAudio']
osx_ldflags +=  ['-Wl,-framework,ForceFeedback']
osx_ldflags +=  ['-Wl,-framework,GameController']
osx_ldflags +=  ['-Wl,-framework,SystemExtensions']
osx_ldflags +=  ['-Wl,-framework,DeviceCheck']
osx_ldflags +=  ['-Wl,-framework,AudioUnit']
osx_ldflags +=  ['-Wl,-framework,AudioToolbox']
osx_ldflags +=  ['-Wl,-framework,CoreHaptics']
osx_ldflags +=  ['-Wl,-framework,Carbon']
osx_ldflags +=  ['-Wl,-framework,Metal']
osx_ldflags +=  ['-Wl,-framework,MetalKit']
osx_ldflags +=  ['-Wl,-framework,ApplicationServices']
osx_ldflags +=  ['-Wl,-framework,QuartzCore']
osx_ldflags +=  ['-Wl,-framework,ICADevices']
osx_ldflags +=  ['-Wl,-framework,DeviceCheck']
osx_ldflags +=  ['-Wl,-framework,Foundation']
osx_ldflags +=  ['-Wl,-framework,AppKit']
osx_ldflags +=  ['-Wl,-framework,IOKit']
osx_ldflags +=  ['-Wl,-framework,Security']

osx_audit_flags +=  ['-lbsm']

#osx_wg_flags +=  ['-MMD']
#osx_wg_flags +=  ['-MP']
#osx_wg_flags +=  ['-DRUNSTATEDIR=/var/run']
osx_wg_flags +=  ['-DRWIMG_PNG']
osx_wg_flags +=  ['-DRWIMG_JPEG']
osx_wg_flags +=  ['-DRWIMG_GIF']

osx_img_flags +=  ['-lpng']
osx_img_flags +=  ['-ljpeg']
osx_img_flags +=  ['-lgif']
osx_img_flags +=  ['-l','iconv']

add_global_link_arguments(osx_ldflags,     language : ['c'])
add_global_link_arguments(osx_audit_flags, language : ['c'])
add_global_link_arguments(osx_wg_flags, language : ['c'])
add_global_link_arguments(osx_img_flags, language : ['c'])

osx_link_args = osx_ldflags


