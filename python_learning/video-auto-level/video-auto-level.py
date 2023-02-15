# video-auto-level.py
# Ryan Jensen
# 2019-03-03
"""auto-levels the color of a batch of videos in a directory"""

import os

# All files in this directory will be auto-leveled:
directory_input = "A:/Videos/See Magnetic Fields in 3D/"
# color-corrected videos are saved to this sub-directory:
directory_output = directory_input + "auto-level/"
# this is added to filenames to differentiate them from the originals:
suffix = "_al"

codec = ""
filter = "-vf pp=autolevels"

files = os.listdir(directory_input)
try:
    os.mkdir(directory_output)
except:
    _ = 0 # do nothing

for f in files:
    (file_name, file_ext) = os.path.splitext(f) 
    command = \
        "ffmpeg -i \"" + directory_input + f + "\" " \
        + codec + " " \
        + filter + " " \
        + "\"" + directory_output + file_name + suffix + file_ext + "\""
    os.system(command)
