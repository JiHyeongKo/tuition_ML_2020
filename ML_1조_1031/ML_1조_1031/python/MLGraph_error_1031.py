import matplotlib.pyplot as plt
import numpy as np
import sys
MAX_COUNT = 100

File = open('write_error.txt', 'r', encoding = 'utf-8')
data = File.readline()

epoch_array=[]
error_array=[]

for i in range(0, MAX_COUNT, 1):
    epoch_array.append(0)
    error_array.append(0)

    

for k in range(0, MAX_COUNT, 1):
    lineBuffer = File.readline()
    line = (lineBuffer.rstrip('\t'))
    epoch_buffer = line[0:7]
    error_buffer = line[8:14]
    epoch_array[k] = epoch_buffer
    error_array[k] = error_buffer
    enter = File.readline()
    
plt.grid()
plt.xlabel('EPOCH')
plt.ylabel('ERROR')
plt.scatter(epoch_array, error_array)
plt.show()

File.close()
