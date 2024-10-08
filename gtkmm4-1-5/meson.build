# .

# rsync -arvu --delete --delete-excluded --exclude=_build/ stage/ gtkmm4-1-5/

# meson setup _build [--reconfigure]
# meson compile -C _build [run]

# i18n:
# to add/remove langs:
# edit LINGUAS as need it, then:
# meson setup _build --reconfigure
# regenerate POTFILES with sources files
# meson compile -C _build potfiles
# extract strings from soueces
# meson compile -C _build gtkmm4-update-po
# edit po files as need it, then build
# meson compile -C _build

project('gtkmm4', 'cpp', version: '1.5.0.0', default_options: ['cpp_std=c++17', 'warning_level=3'])

IS_WIN = (build_machine.system() == 'windows') ? true : false

FS = import('fs')

gtkmm4_dep = dependency('gtkmm-4.0', version: '>= 4.10.0')

PROGRAM_GTK_CSD = get_option('USE_GTK_CSD')

PROGRAM_NAME    = meson.project_name()
PROGRAM_VERSION = meson.project_version()
PROGRAM_DESC    = 'Gtkmm4 hard-coded application demo'
PROGRAM_ID      = f'gtkmm4.aullidolunar.@PROGRAM_NAME@'
PROGRAM_RC_PATH = '/@0@'.format(PROGRAM_ID.replace('.', '/'))
PROGRAM_TITLE   = f'@PROGRAM_NAME@ @PROGRAM_VERSION@'
PROGRAM_DEFS    = [
  f'-DPROGRAM_NAME="@PROGRAM_NAME@"',
  f'-DPROGRAM_VERSION="@PROGRAM_VERSION@"',
  f'-DPROGRAM_DESC="@PROGRAM_DESC@"',
  f'-DPROGRAM_ID="@PROGRAM_ID@"',
  f'-DPROGRAM_RC_PATH="@PROGRAM_RC_PATH@"',
  f'-DPROGRAM_GTK_CSD="@PROGRAM_GTK_CSD@"',
]

if get_option('USE_CAIRO')
  PROGRAM_DEFS += f'-DWITH_CAIRO'
endif

PROGRAM_INCDIRS = []
PROGRAM_SOURCES = []
I18N_SOURCES    = []
I18N_DEPS       = []

subdir('scripts')
subdir('src')
subdir('data')
subdir('locale')

program_executable = executable(
  PROGRAM_NAME,
  PROGRAM_SOURCES,
  I18N_DEPS,
  dependencies: gtkmm4_dep,
  include_directories: PROGRAM_INCDIRS,
  cpp_args: PROGRAM_DEFS,
  native: true
)

run_target(
  'run',
  command: [
    program_executable
  ]
)

zip_path = find_program('7z')

project_dir = FS.parent(meson.project_build_root())

run_target(
  'zip',
  command: [
    zip_path,
    'a',
    '-t7z',
    '-xr!*_build',
    f'@PROGRAM_NAME@-@PROGRAM_VERSION@-src.7z',
    project_dir
  ]
)