import os
import subprocess

options_nm = '-gjnopruU'
options_otool = 'dt'

test_dir = 'tests/'
test_subdirs = ['fat/', 'mach32_be/', 'mach32_le/', 'mach64/']

def test(command, options):
	for option in options:
		print()
		print('\033[1;36;40m------- Test of ft_{} with option {} -------'\
			.format(command, option))
		for subdir in test_subdirs:
			print()
			print('\033[1;33;40mTest for {} files:'.format(subdir[:-1]))
			for binary in os.listdir(test_dir + subdir):
				ref_output = subprocess.check_output([command, '-' + option,
						test_dir + subdir + binary])
				my_output =  subprocess.check_output(['./ft_' + command, '-' + option,
						test_dir + subdir + binary])
				print('\033[1;37;40m{:<35}: '.format(binary), end='')
				if ref_output == my_output:
					print('\033[1;32;40m No diff :)')
				else:
					print('\033[1;31;40m Diff :(')
	print('\033[1;37;40m')

if __name__ == '__main__':

	test('nm', options_nm)
	test('otool', options_otool)
