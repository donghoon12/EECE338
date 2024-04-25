# Inspect versions of listed python modules 
# 
# Author: hyunsungkim (hyunsungkim@postech.ac.kr)
# Last modified: 2021-03-09

import sys

print("Python Version: {}".format(sys.version))

#pipmodules = ['numpy', 'scipy', 'matplotlib', 'pillow']  # List of python modules to be inspected
pipmodules = ['pigpio']
for module in pipmodules:
    try:
        print("Inspecting module {}".format(module))
        module_obj = __import__(module)
        print("Version: ", module_obj.__version__, "\n")
    except ImportError:
        sys.stderr.write("ERROR: missing python module: " + module + "\n")
        print()
