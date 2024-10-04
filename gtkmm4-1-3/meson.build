# .

# rsync -rvu -tpgo --exclude=_build/ --delete gtkmm4-1-2_staged/ gtkmm4-1-2/

# meson setup _build [--reconfigure]
# meson compile -C _build [run]
# i18n:
# meson compile -C _build gtkmm4-update-po

project('gtkmm4', 'cpp', version: '1.3.0.0', default_options: ['cpp_std=c++17', 'warning_level=3'])

IS_WIN = (build_machine.system() == 'windows') ? true : false

FS = import('fs')

gtkmm4_dep = dependency('gtkmm-4.0', version: '>= 4.8.0')

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
  f'-DPROGRAM_TITLE="@PROGRAM_TITLE@"',
  f'-DPROGRAM_ID="@PROGRAM_ID@"',
  f'-DPROGRAM_RC_PATH="@PROGRAM_RC_PATH@"',
  f'-DPROGRAM_GTK_CSD="@PROGRAM_GTK_CSD@"',
  f'-DPROGRAM_DESC="@PROGRAM_DESC@"'
]

if get_option('USE_CAIRO')
  PROGRAM_DEFS += [
    f'-DWITH_CAIRO'
  ]
endif

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