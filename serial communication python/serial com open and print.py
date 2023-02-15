# This should open a com port and write/read data to/from it
import os
import serial
ser = serial.Serial('COM4',600)
os.system('pause')
ser.write(b'hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh')
os.system('pause')

#print( ser.readline() )

# setup script for py2exe to create the miniterm.exe
#
# (C) 2001-2015 Chris Liechti <cliechti@gmx.net>
#
# SPDX-License-Identifier:    BSD-3-Clause

# from distutils.core import setup
# import sys

# sys.path.insert(0, '..')

# import serial.tools.miniterm


# sys.argv.extend("py2exe --bundle 1".split())

# setup(
    # name='miniterm',
    # zipfile=None,
    # options={"py2exe": {
        # 'dll_excludes': [],
        # 'includes': [
                # 'serial.urlhandler.protocol_hwgrep', 'serial.urlhandler.protocol_rfc2217',
                # 'serial.urlhandler.protocol_socket', 'serial.urlhandler.protocol_loop'],
        # 'dist_dir': 'bin',
        # 'excludes': ['serialjava', 'serialposix', 'serialcli'],
        # 'compressed': 1,
        # }
    # },
    # console=[
        # serial.tools.miniterm.__file__
    # ],
# )