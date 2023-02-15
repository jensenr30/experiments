"""Regenerate songs using sound clips.

Generically, this module will be capable of regenerating any discrete sampled
waveform with any other discrete sampled waveform.

(c) Ryan Jensen 2019"""
#===============================================================================
# import modules
#===============================================================================
# use for 
import math

# used for storing signal data, and for more efficient array operations
import numpy as np

# used for importing .wav files
from scipy.io import wavfile

# used to plot signals (mainly debugging as of 2019-02-25)
import matplotlib
#from builtins import str
from PIL.ImageChops import offset
matplotlib.use('TkAgg')
from matplotlib import pyplot
# used to copy signals
import copy
import enum




#===============================================================================
# attributes
#===============================================================================
# the default attributes define the format to which all signals are converted
# before cross-correlation and other manipulations can be performed.
# the default sample rate (samples/second) 
fs_default = 48000
# default data type used to encode scalar data in audio waveforms
dtype_default = np.float32
type_default = float
# the number of decimals places to round to when you display a signal's time
time_decimal_places = 9


#===============================================================================
# classes
#===============================================================================
class signal:
    """Contains raw audio data with arbitrary number of channels.
    
    In this context, "audio data" is defined as a sequence of scalar values.
    All audio data has an associated sample rate [fs] withh units
    = samples / second)."""
    
    # name of this signal (arbitrary - strictly for user readability)
    name = "UNNAMED SIGNAL"
    # name of the file from which this signal was copied 
    source_file_name = "NOT LOADED FROM FILE"
    # this contains the raw audio data, sample-by-sample.
    samples = np.array(0)
    # sample rate of the signal in samples/second.
    fs = 1
    # original audio file (before sample rate and bit depth were standardized)
    
    
    def __init__(self, nsamples=0, nchannels=1, fs=1, name=None):
        """Instantiate and return a new signal."""
        self.samples = np.ndarray((nsamples,nchannels),dtype_default)
        self.fs = fs
        if name:
            self.name = name
    
    
    def copy(self):
        """Creates (and returns) a duplicate object with the same information."""
        return copy.deepcopy(self)
    
    
    def is_empty(self):
        """Return true if the signal is empty, otherwise return false.
        
        If the number of channels OR the number of samples is 0, the signal is
        empty and this function will return true."""
        return ((self.nchannels() == 0) or (self.nsamples() == 0))
    
    
    def nchannels(self):
        """Return the number of channels that exist in the signal."""
        if self.samples.ndim == 1:
            chans = 1
        elif self.samples.ndim == 2:
            (_,chans) = self.samples.shape
        else:
            raise NameError('samples numpy array is not 1- or 2-dimensional.') 
        return chans
    
    
    def nsamples(self):
        """Returns the number of samples of the signal."""
        shape = self.samples.shape
        return shape[0]
    
    
    def time(self):
        """Returns the duration of the signal in seconds.
        
        Example: if the signal has 1000 samples and the sample rate is 48 kHz,
        then the time is 1000/48000 = 20.833333 ms"""
        return self.nsamples() / self.fs
    
    
    def get_signal_type_name(self):
        """Returns the name of the type of audio (mono, stereo, 4-channel, etc.)"""
        chans = self.nchannels()
        names = {0:"empty", 1:"mono", 2:"stereo"}
        try:
            return names[chans]
        except KeyError:
            return str(chans) + "-channel"
    
    
    def get_channel_name(self,channel):
        """Returns the name of the channel, given the input channel number."""
        if channel < 0:
            raise NameError("[channel] cannot be negative.")
        if channel >= self.nchannels():
            raise NameError("[channel] exceeds signal's number of channels.")
        if channel//1 != channel:
            raise NameError("[channel] must be an integer.")
        if channel == 0:
            return "left"
        elif channel == 1:
            return "right"
        else:
            return "channel-" + str(channel)
    
    
    def print_info(self):
        """Print some information about the signal to the console."""
        print("\"" + str(self.name) + "\":")
        print("source file =    \"" + str(self.source_file_name) + "\"")
        print("total samples =  " + str(self.nsamples()))
        print("sample rate =    " + str(self.fs) + " Hz")
        print("time =           " + str(round(self.time(),time_decimal_places)) + " s")
        print("channels =       " + str(self.nchannels()))
        print("dtype =          " + str(self.samples.dtype))
    
    
    def plot(self):
        pyplot.ion()
        fig = pyplot.figure()
        ax = pyplot.subplot(1,1,1)
        ax.set_xlabel('Time')
        ax.set_ylabel('Value')
        t = np.array(list(range(self.nsamples())))/self.fs
        y = self.samples[:,0]           # TODO: plot all waveforms on the same plot
        ax.plot(t, y)
        fig.show()
        return fig
    
    
    def change_speed(self, rate):
        """Modify the playback speed of the 'input signal' (only by changing fs) 
        
        Set the sample frequency (fs) to a (fs*rate) in order to effectively
        change the playback speed of the signal."""
        assert isinstance(rate, type_default)
        self.fs *= rate
    
    
    def resample(self, fs_new):
        """generates new signal 'sig_new' at new sample frequency 'fs_new' by
        re-sampling self signal 'self'. 
        
        TODO: implement a better resampling function which limits frequency
        content to 1/2 of the lowest sampling frequency involved.  probably use
        a sinc function"""
        # calculate the length (seconds) of the original signal
        nsamples_new = (self.time() * fs_new) / 1
        # convert nsamples_new to an integer.  use math.floor(): this will
        # ensure we are always interpolating and never extrapolating.
        # practical warning: this operation may leave you with an output signal
        # that has a SLIGHTLY different duration.
        nsamples_new = math.floor(nsamples_new)
        # generate a new signal with the same time, but different sample rate
        sig_new = signal(nsamples_new,self.nchannels(),fs_new)
        
        max_freq = min(sig_new.fs,self.fs)/2.0
        # TODO generate sinc function with frequency of [max_freq].
        sig_sinc = sinc(max_freq,)
        # TODO convolve the sinc function with the old 
        # TODO: test this function
        # TODO: write this function
        
        return sig_new
    
    
    def save(self, filename):
        """saves audio signal to 'filename' on your file-system."""
        # TODO: make sure this function can write more formats that just .wav
        wavfile.write(filename, self.fs, self.samples)
    
    
    
    
    
    
# end signal

#===============================================================================
# functions
#===============================================================================
def load(filename):
    """reads audio signal from file."""
    # TODO: test this function
    # TODO: make sure this function can read  more formats that just .wav
    sig = signal()
    sig.name = filename
    sig.source_file_name = filename
    (sig.fs,sig.samples) = wavfile.read(filename)
    # TODO convert signal samples.dtype to default dtype 
    # TODO: resample at default sample rate
    return sig



def correlate(sig1, sig2, ):
    """Cross-correlate sig2 with sig1."""
    # TODO: test this function
    # TODO: write this function



def dot_product(npa1, npa2):
    """Perform dot_product between two numpy arrays (1-D vectors)."""
    # TODO: test this function
    # TODO: be able to handle different data types(or is this unnecessary
    # due to the fact that all signals should have the same data type?)
    # get the shapes of each numpy vector
    shape1 = npa1.shape
    shape2 = npa2.shape
    # the two numpy vectors must have the same shape
    if(shape1 != shape2):
        raise NameError("numpy array shapes do not match!")
    return np.dot(npa1, npa2)



def sinc(f, fs, N):
    """Generates sinc() 1-D signal.
    
    'f' is the frequency of the sinc() function.  e.g. 24000 Hz
    'fs' sample frequency of the signal.  e.g. 48000 Hz
    'N' is the number of periods of the sinc function to generate on either
    side of 0."""
    # TODO: test this function
    # enforce data types
    f = type_default(f)
    fs = type_default(fs)
    N = type_default(N)
    assert isinstance(f, type_default)
    assert isinstance(fs, type_default)
    assert isinstance(N, type_default)
    # specify signal name
    name = 'sinc'
    # calculate the number of samples needed to calculate sinc on one side of 0
    # (not including 0)
    nsamples_one_side = round(N * fs / f)
    if nsamples_one_side < 1:
        return signal(1, 1, fs, name)
    # allocate the 'output' signal
    nsamples = nsamples_one_side*2 + 1
    output = signal(nsamples, 1, fs, name)
    # calculate the normalized "time-step" (units are actually radians/sample)
    t_norm = 2 * math.pi * f / fs
    t = 0
    output.samples[nsamples_one_side] = 1
    # generate sinc function on both sides of 0 simultaneously symmetrically
    for i in range(nsamples_one_side):
        t += t_norm
        try:
            sinc_val_i = math.sin(t) / t
        except ZeroDivisionError:
            sinc_val_i = 1
        output.samples[nsamples_one_side + 1 + i] = sinc_val_i
        output.samples[nsamples_one_side - 1 - i] = sinc_val_i
    return output


def regenerate(target, bases, options={}):
    """"Regenerate the 'target' audio using some combination of the 'bases'.
    
    Inputs:
        target
            signal
            The waveform that you want to regenerate using the bases signals.
        bases
            [signal, signal, signal, ...]
            A list of signals that will serve as basis signals when regenerating
            the target. 
        options
            {'opt1':55, 'opt2':"Ryan", 'opt3':1}
            A dictionary of different options that the user wants to specify.
            Here is a list of all supported Arguments, and example values
                
                'sample_rate':48000
                    Explicitly set the sample rate.
                    If you do not set the sample rate, it will be automatically
                    selected by calculating the maximum sample rate of all basis
                    signals and the target signal.
                    
                '
    """
    #---------------------------------------------------------------------------
    # ensure that all input variables have the correct type
    #---------------------------------------------------------------------------
    assert isinstance(target, signal),  "not the right type.  {}".format(target)
    assert isinstance(bases, list),    "not the right type.  {}".format(bases)
    assert isinstance(options, dict),    "not the right type.  {}".format(options)
    
    #---------------------------------------------------------------------------
    # validate each basis signal
    #---------------------------------------------------------------------------
    for b in range(bases):
        basis = bases[b]
        assert type(basis) is signal,   "bases[{}] not the right type.  {}".format(b, basis)
    
    #---------------------------------------------------------------------------
    # calculate 'fs', the master sample rate to use
    #---------------------------------------------------------------------------
    fs = target.fs = target.fs
    for basis in bases:
        fs = max(fs, basis.fs)
    
    #---------------------------------------------------------------------------
    # convert target and all bases to the same sample-rate.
    #---------------------------------------------------------------------------
    target = target.resample(fs)
    for b in range(bases):
        bases[b] = bases[b].resample(fs)
    
    #---------------------------------------------------------------------------
    # set up signals
    #---------------------------------------------------------------------------
    # create the 'regen' signal.  It holds the current approximation of the
    # 'input' signal.
    regen = signal()
    # create the error signal that holds the current error between 'regen', (the
    # regenerated signal) and 'input' (the original signal).
    regen = signal()
    
    #---------------------------------------------------------------------------
    # set up regeneration history
    #---------------------------------------------------------------------------
    # this is a list of tuples that specify how the audio track was regenerated:
    # [ signal_file_name.wav, gain, 
    
    
    
    
    
    
