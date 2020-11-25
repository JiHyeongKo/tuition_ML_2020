import matplotlib.pyplot as plt
import numpy as np
import sys
MAX_COUNT = 100

File = open('write_evaluate_1.txt', 'r', encoding = 'utf-8')
data = File.readline()

epoch_array=[]
error_array=[]

for i in range(0, MAX_COUNT, 1):
    epoch_array.append(0)
    error_array.append(0)

for k in range(0, MAX_COUNT, 1):
    lineBuffer = File.readline()
    line = (lineBuffer.rstrip())
    epoch_buffer = line[0:8]
    error_buffer = line[9:18]
    epoch_array[k] = epoch_buffer
    error_array[k] = error_buffer

for i in range(1, MAX_COUNT, 1):
    if ( epoch_array[i] == '') or (epoch_array[i] == '\n'):
        epoch_array[i]=epoch_array[i-1]
    if ( error_array[i] == '') or (error_array[i] == '\n'):
        error_array[i]=error_array[i-1]

for i in range(0, MAX_COUNT, 1):
    epoch_array[i] = float(epoch_array[i])
    error_array[i] = float(error_array[i])

plt.axis([0, MAX_COUNT, 0 ,error_array[0]])
plt.grid(b=True, which='both', axis='both')
plt.xlabel('EPOCH')
plt.ylabel('ERROR')
plt.scatter(epoch_array, error_array)
plt.show()

File.close()
