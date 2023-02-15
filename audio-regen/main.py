"""Main python script for the AudioRegen project

(c) Ryan Jensen 2019"""
#from scipy import signal
print("====================")
print("AudioRegen Start!")
print("====================")


#-------------------------------------------------------------------------------
# modules
#-------------------------------------------------------------------------------
import audio_regen as ar


#-------------------------------------------------------------------------------
# initial code to test functions - just getting started
#-------------------------------------------------------------------------------
ste = ar.load("left-is-square_right-is-sine.wav")
ste.print_info()
saw =  ar.load("sawtooth-mono-1kHz-41kHz-32-bit-float.wav")
saw.print_info()

epiano = ar.load("epiano_single.wav")
epiano.print_info()
epiano_song = ar.load("epiano_multiple.wav")
epiano_song.print_info()


# create a test signal to test audio_regen code
ch = 1          # number of channels
fs = 48000      # sample rate (Hz)
N = 100          # samples
ramp = ar.signal(N, ch, fs, name="test signal")

for i in range(0,ramp.nsamples()):
    ramp.samples[i] = i

ramp.print_info()
ramp.plot()

#fig_ste = ste.plot()
#fig_epiano = epiano.plot()


print("====================")
print("AudioRegen End.")
print("====================")

