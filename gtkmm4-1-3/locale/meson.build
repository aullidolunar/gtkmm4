# locale

i18n = import('i18n')

# Read locales:
langs = FS.read('LINGUAS').strip().split('\n')

po_paths = []
foreach lang: langs
  po_file = meson.current_source_dir() / '@0@.po'.format(lang)
  if not FS.exists(po_file)
    run_command(
      PYTHON_EXECUTABLE,
      PY_SCRIPTS[0], # touch.py
      po_file,
      check: true
    )
  endif
  po_paths += po_file
endforeach

# Save current source files with translatable strings in POTFILES:
run_command(
  PYTHON_EXECUTABLE,
  PY_SCRIPTS[1], # potfiles.py
  meson.current_source_dir(),
  I18N_SOURCES,
  check: true
)
	
gettext = i18n.gettext(
  meson.project_name(),
  args: [
    '--from-code=UTF-8',
    '--msgid-bugs-address="aullidolunar@gmail.com"',
    f'--package-name="@PROGRAM_NAME@"',
    f'--package-version="@PROGRAM_VERSION@"'
  ]
)

desktopfile = custom_target(
  input: [DESKTOP_FILE_IN, po_paths],
  output: '@BASENAME0@',
  command: [
    'msgfmt',
    '--desktop',
    '--template=@INPUT0@',
    '-d',
    meson.current_source_dir(),
    '-o',
    '@OUTPUT0@'
  ]
)

# build mo files and generate desktop file with executable:
I18N_DEPS += [gettext[0], desktopfile]
