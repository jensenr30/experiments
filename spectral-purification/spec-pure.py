# eliminate low-level components in frequency domain.
# Ryan Jensen
# June 2021
# possible application: an audio signal that has a poor-mediocre signal-to-noise level (such as 20 or 40) could be made to have infinite signal-to-noise ratio by setting all low-level frequency components to 0.  This is non-linear action in the frequency domain.  This will create "sharp edges" in the spectrum where the components cross the amplitude threshold.  Perhaps there is a way to smoothly transition from [multiplication-of-noise-by-0] to [multiplication-of-signal-by-1].  Maybe the sigmoid function could be used as a multiplication-mask to ease the transition between noise and signal.  I wonder if anyone else has done this already for audio?

# include libraries


# import audio

# define filtering parameters

# apply the filter

# export signal

