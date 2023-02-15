# dir_parent_rename.py
# Ryan Jensen
# 2019-03-30
# used to rename all the folders in my Frank Zappa discography to something more sensible.

import os, sys, re

dir_parent = "A:/Music/EXTERNAL/Frank Zappa/"
wd = os.listdir(dir_parent)
print("Found " + str(len(wd)) + " items in parent directory.")

reg_ex = r"\) Frank Zappa - \d{2} -"
new_ex = ")"

reg_ex2 = r" \[\d{3}\]"
new_ex2 = ""

for i,dir_old in enumerate(wd):
    print(str(i+1) + ":")
    print("\told:\t" + dir_old)
    
    # calculate new directory name
    dir_new = re.sub(reg_ex, new_ex, dir_old)
    dir_new = re.sub(reg_ex2, new_ex2, dir_new)
    print("\tnew:\t" + dir_new)
    
    os.rename(dir_parent + dir_old, dir_parent + dir_new)
    
    print("")

