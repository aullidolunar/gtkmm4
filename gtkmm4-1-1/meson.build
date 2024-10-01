# .

# meson setup _build [--reconfigure]
# meson compile -C _build [run]

project('gtkmm4', 'cpp', version: '1.1.0.0', default_options: ['cpp_std=c++17', 'warning_level=3'])

FS = import('fs')

gtkmm4_dep = dependency('gtkmm-4.0', version: '>= 4.8.0')

PROGRAM_GTK_CSD = get_option('USE_GTK_CSD')

PROGRAM_NAME    = meson.project_name()
PROGRAM_VERSION = meson.project_version()
PROGRAM_ID      = f'gtkmm4.aullidolunar.@PROGRAM_NAME@'
PROGRAM_TITLE   = f'@PROGRAM_NAME@ @PROGRAM_VERSION@'
PROGRAM_DEFS    = [
  '-DPROGRAM_NAME="' + PROGRAM_NAME + '"',
  '-DPROGRAM_VERSION="' + PROGRAM_VERSION + '"',
  '-DPROGRAM_TITLE="' + PROGRAM_TITLE + '"',
  '-DPROGRAM_ID="' + PROGRAM_ID + '"',
  '-DPROGRAM_GTK_CSD="' + PROGRAM_GTK_CSD + '"'
]

PROGRAM_SOURCES = []

subdir('src')

program_executable = executable(
  PROGRAM_NAME,
  PROGRAM_SOURCES,
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
project_channel = FS.stem(project_dir)

run_target(
  'zip',
  command: [
    zip_path,
    'a',
    '-t7z',
    '-xr!*_build',
    f'@project_channel@.7z',
    project_dir
  ]
)