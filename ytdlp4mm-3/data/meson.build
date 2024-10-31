# data

glib_compile_resources_executable = find_program('glib-compile-resources', required: true)

blueprint_executable = find_program('blueprint-compiler', required: true)

builder_glade_file = custom_target(
  input: files('builder.glade.blp'),
  output: '@BASENAME@',
  command: [
    blueprint_executable,
    'compile',
    '--output',
    '@OUTPUT@',
    '@INPUT@'
  ]
)

builder_glade = FS.name(builder_glade_file)

PROGRAM_DEFS += [
  '-DGLADE_FILE="@0@/@1@"'.format(PROGRAM_RC_PATH, builder_glade)
]

main_gresource_xml = configure_file(
  input: files('main.gresource.xml.in'),
  output: '@BASENAME@',
  configuration: {
    'PROGRAM_NAME': PROGRAM_NAME,
    'PROGRAM_RC_PATH': PROGRAM_RC_PATH,
    'GLADE_FILE': builder_glade
  }
)

PROGRAM_SOURCES += custom_target(
  input: [builder_glade_file, main_gresource_xml],
  output: '@PLAINNAME1@.cpp',
  command: [
	glib_compile_resources_executable,
	'--target=@OUTPUT@',
	'--sourcedir=@CURRENT_SOURCE_DIR@',
	'--sourcedir=@OUTDIR@',
	'--generate-source',
	'@INPUT1@'
  ]
)

DESKTOP_FILE_IN = configure_file(
  input: files('desktop.in.in'),
  output: PROGRAM_NAME + '.@BASENAME@',
  configuration: {
    'PROGRAM_NAME': PROGRAM_NAME,
    'PROGRAM_DESC': PROGRAM_DESC,
    'PROGRAM_ICON': meson.current_source_dir() / 'yt16.png'
  }
)

I18N_SOURCES += [
  FS.relative_to(DESKTOP_FILE_IN, meson.project_source_root()),
  FS.relative_to(builder_glade_file, meson.project_source_root())
]

if IS_WIN
  windows = import('windows')
  
  resource = configure_file(
  	input: files('resource.rc.in'),
  	output: '@BASENAME@',
  	configuration: {
  	  'PROGRAM_VERSION': PROGRAM_VERSION,
  	  'PROGRAM_VERSION_COMMA': PROGRAM_VERSION.replace('.', ','),
  	  'BIN_NAME': PROGRAM_NAME, 
  	  'PROGRAM_DESCRIPTION': PROGRAM_DESC
  	}
  )
  
  PROGRAM_SOURCES += windows.compile_resources(
  	resource,
  	include_directories: meson.current_source_dir()
  )
endif
