# phytop.py
# (c) Ryan Jensen 2019
#
# A visual, real-time physics-simulation with parameters controlled by all the processes running on your computer.
import psutil

def get_list_of_processes():
    pl = []
    for proc in psutil.process_iter():
        pl.append(proc)
    return pl

pl = get_list_of_processes()
print(pl)




# TODO:
#
# 1. get system memory (e.g. 22 GB on jenbox)
# 2. get processor cores and speed (e.g. 4, 3.6 GHz on jenbox)
# 3 . get a list of programs with some percentage of CPU used and some percentage of RAM used.  Then we do a log10(of the value) to obtain the dB(CPU usage) and dB(RAM usage).  You get each program's CPU & RAM usage on a log(scale), (basically) for free, because python should support it (in theory).
