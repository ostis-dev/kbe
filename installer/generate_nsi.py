import sys, os

inst = ""#open('install_sections', 'w')
uninst = ""#open('uninstall_section', 'w')

ex_inst = ""
ex_uninst = ""

if __name__ == "__main__":

	if len(sys.argv) < 3:
		print "Usage setcions.py <template nsi file> <output_nsi_file>"
		sys.exit(0)
	
	for (root, dirs, files) in os.walk('sources', False):
		example = root.startswith('sources\example')
		manual = root.startswith('sources\manual')
		plugins = root.startswith('sources\plugins')
		if manual or plugins:
			continue
		if example:
			ex_inst += '\n\tSetOutPath "%s"\n' % root.replace("sources", "$INSTDIR")
		else:
			inst += '\n\tSetOutPath "%s"\n' % root.replace("sources", "$INSTDIR")
		
		for file in files:
			if example:
				ex_inst += '\tFile "%s"\n' % os.path.join(root, file)
				ex_uninst += '\tDelete "%s"\n' % os.path.join(root.replace("sources", "$INSTDIR"), file)
			else:
				inst += '\tFile "%s"\n' % os.path.join(root, file)
				uninst += '\tDelete "%s"\n' % os.path.join(root.replace("sources", "$INSTDIR"), file)
		
		if example:
			ex_uninst += '\n\tRMDir "%s"\n' % root.replace("sources", "$INSTDIR")
		else:
			uninst += '\n\tRMDir "%s"\n' % root.replace("sources", "$INSTDIR")

	input = open(sys.argv[1], 'r')
	data = input.read()
	input.close()
	
	output = open(sys.argv[2], 'w')
	data = data.replace("%INST_FILES%", inst)
	data = data.replace("%UNINST_FILES%", uninst)
	data = data.replace("%INST_EXAMPLE%", ex_inst)
	data = data.replace("%UNINST_EXAMPLE%", ex_uninst)
	output.write(data)
	output.close()
	