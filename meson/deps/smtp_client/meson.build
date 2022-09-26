smtp_client_system_headers = [

]
smtp_client_local_headers = [
  'smtp_client/src/SMTPMail.h',
  'smtp_client/src/smtp.h',
  'smtp_client/test/seams.h',
]
smtp_client_srcs = [
  '../../../submodules/smtp_client/src/mailx.c',
  '../../../submodules/smtp_client/src/smtp.c',
]

smtp_client_dirs = [
  '../../../submodules/smtp_client',
  '../../../submodules/smtp_client/src',
  inc,
]

smtp_client_deps = [

]

if smtp_client_srcs.length() > 0
  smtp_client_lib =library('smtp_client',
    files(smtp_client_srcs),
    install: false,
    dependencies: smtp_client_deps,
    include_directories: smtp_client_dirs,
  )
  smtp_client_links = [smtp_client_lib]
else
  smtp_client_links = []
endif

smtp_client_dep = declare_dependency(
  include_directories: smtp_client_dirs,
  link_with: smtp_client_links,
)
