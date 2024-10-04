# python potfiles.py locale_dir sources_list

import os
import sys

locale_dir = sys.argv[1]
sources_list = sys.argv[2:]

saved_cwd = os.getcwd()
os.chdir(locale_dir)

with open('POTFILES', 'w') as pf:
	content = '\n'.join(sources_list)
	pf.write(content)

os.chdir(saved_cwd)
