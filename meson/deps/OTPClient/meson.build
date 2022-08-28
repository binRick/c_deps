OTPClient_srcs = [files(
  '../../../submodules/OTPClient/src/add-common.c',
  '../../../submodules/OTPClient/src/add-from-qr.c',
  '../../../submodules/OTPClient/src/app.c',
  '../../../submodules/OTPClient/src/authplus.c',
  '../../../submodules/OTPClient/src/change-db-cb.c',
  '../../../submodules/OTPClient/src/change-file-cb.c',
  '../../../submodules/OTPClient/src/cli/get-data.c',
  '../../../submodules/OTPClient/src/cli/help.c',
  '../../../submodules/OTPClient/src/common/aegis.c',
  '../../../submodules/OTPClient/src/common/andotp.c',
  '../../../submodules/OTPClient/src/common/common.c',
  '../../../submodules/OTPClient/src/common/freeotp.c',
  '../../../submodules/OTPClient/src/db-actions.c',
  '../../../submodules/OTPClient/src/db-misc.c',
  '../../../submodules/OTPClient/src/edit-data.c',
  '../../../submodules/OTPClient/src/exports.c',
  '../../../submodules/OTPClient/src/file-size.c',
  '../../../submodules/OTPClient/src/get-builder.c',
  '../../../submodules/OTPClient/src/google-migration.pb-c.c',
  '../../../submodules/OTPClient/src/gquarks.c',
  '../../../submodules/OTPClient/src/gui-common.c',
  '../../../submodules/OTPClient/src/imports.c',
  '../../../submodules/OTPClient/src/liststore-misc.c',
  '../../../submodules/OTPClient/src/lock-app.c',
  '../../../submodules/OTPClient/src/manual-add-cb.c',
  '../../../submodules/OTPClient/src/message-dialogs.c',
  '../../../submodules/OTPClient/src/new-db-cb.c',
  '../../../submodules/OTPClient/src/parse-data.c',
  '../../../submodules/OTPClient/src/parse-uri.c',
  '../../../submodules/OTPClient/src/password-cb.c',
  '../../../submodules/OTPClient/src/qrcode-parser.c',
  '../../../submodules/OTPClient/src/secret-schema.c',
  '../../../submodules/OTPClient/src/settings.c',
  '../../../submodules/OTPClient/src/shortcuts.c',
  '../../../submodules/OTPClient/src/treeview.c',
  '../../../submodules/OTPClient/src/webcam-add-cb.c',
)]

OTPClient_dirs = [
  '../../../submodules/OTPClient',
  '../../../submodules/OTPClient/flatpak',
  '../../../submodules/OTPClient/proto',
  '../../../submodules/OTPClient/src',
  '../../../submodules/OTPClient/src/cli',
  '../../../submodules/OTPClient/src/common',
  '../../../submodules/OTPClient/src/ui',
  inc,
]

OTPClient_deps = [

]

OTPClient_lib = static_library('OTPClient',
  OTPClient_srcs,
  install: false,
  dependencies: OTPClient_deps,
  include_directories: OTPClient_dirs,
)

OTPClient_dep = declare_dependency(
  include_directories: OTPClient_dirs,
  link_with: OTPClient_lib,
)
