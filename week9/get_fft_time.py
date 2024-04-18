import numpy as np
import scipy.io as sio
import scipy.io.wavfile
import matplotlib.pyplot as plt
import argparse 
import time
from scipy import fftpack

parser = argparse.ArgumentParser()
parser.add_argument('--filename', required=False, default='filename.wav')
args = parser.parse_args()

print("drawing plot for", args.filename)

start_time=time.time()
samplerate, data = sio.wavfile.read(args.filename)
fftsize = len(data)
data_fft = fftpack.fft(data, fftsize)
end_time=time.time()

print(start_time-end_time)

# fast fourier transform 
