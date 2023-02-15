import audio_regen as ar
import numpy as np
import time

#===============================================================================
# test signal copying - ensure the copy points to different variables.
#===============================================================================
t_start = time.time()
# create first signal
sig1 = ar.signal()
sig1.fs = 1
sig1.name = 'one'
sig1.samples = np.ndarray((1,1), np.float32)
sig1.source_file_name = 'one.wav'

# create a copy of the first signal
sig2 = sig1.copy()
# but modify each part of it
sig2.fs = 2
sig2.name = 'two'
sig2.samples[0][0] += 1
sig2.source_file_name = 'none'

# make sure that the two signals are different in every way, to prove that the
# copy method is really creating another entire copy of the original signal
assert sig1 != sig2
assert sig1.fs != sig2.fs
assert sig1.name != sig2.name
assert sig1.samples[0][0] != sig2.samples[0][0]
assert sig1.source_file_name != sig2.source_file_name

t_dur = time.time() - t_start
print("Signal copy test completed. Duration = {:.6f} seconds.\n".format(t_dur))


#===============================================================================
# test sinc function generation 
#===============================================================================
t_start = time.time()
# generate the sinc function
sinc = ar.sinc(440, 48000, 5)
sinc.print_info()
sinc.plot()


t_dur = time.time() - t_start
print("sinc generation test completed. Duration = {:.6f} seconds.\n".format(t_dur))


#===============================================================================
# test up-sampling a signal, then down-sampling; ensure error is acceptably low
# and within the range of expectation.
#===============================================================================
# TODO: write this function


