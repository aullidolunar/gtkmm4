# src

sources = files('main.cpp', 'MainWindow.cpp')

foreach src: sources
  I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach

PROGRAM_SOURCES += sources
