# load_song.py
# Ryan Jensen
# 2019-01-20
# test out loading wave files.


from scipy.io import wavfile

#song =          wave.open("epiano_single.wav",'rb')
#basis_vector =  wave.open("epiano_single.wav",'rb')

fs,song = wavfile.read("right-sine_left-cosine.wav")

left = song[:,0]
right = song[:,1]

