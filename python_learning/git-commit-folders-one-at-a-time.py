import os
import subprocess

# target repository
os.chdir('A:/repos/exp')

# get list of directories in working directory.
dirs = [d for d in os.listdir(".") if os.path.isdir(d)]

# commit each directory, one at a time.
for d in dirs:
    if d == '.git':
        continue
    cmd = ["git", "add", d]
    subprocess.run(cmd, check=True)
    cmd = ["git", "commit", "-m", f"Adding {d} directory"]
    try:
        subprocess.run(cmd, check=True)
    except:
        print(f"Could not add directory: {d}")
