import matplotlib.pyplot as plt
import numpy as np
import sys

MAX_DATA = 100
MAX_COUNT = MAX_DATA * MAX_DATA

File = open('grid_test.txt', 'r', encoding = 'utf-8')
data = File.readline()

x1_array=[]
x2_array=[]
grid_array=[]

for i in range(0, MAX_COUNT, 1):
    x1_array.append(0)
    x2_array.append(0)
    grid_array.append(0)

for k in range(0, MAX_COUNT, 1):
    lineBuffer = File.readline()
    line = (lineBuffer.rstrip())
    x1_buffer = line[0:9]
    x2_buffer = line[10:19]
    grid_buffer = line[20:22]
    x1_array[k] = x1_buffer
    x2_array[k] = x2_buffer
    grid_array[k] = grid_buffer

for i in range(1, MAX_COUNT, 1):
    if ( x1_array[i] == '') or (x1_array[i] == '\n'):
        x1_array[i]=x1_array[i-1]
    if ( x2_array[i] == '') or (x2_array[i] == '\n'):
        x2_array[i]=x2_array[i-1]
    if ( grid_array[i] == '') or (grid_array[i] == '\n'):
        grid_array[i]=grid_array[i-1]

for i in range(0, MAX_COUNT, 1):
    x1_array[i] = float(x1_array[i])
    x2_array[i] = float(x2_array[i])
    grid_array[i] = float(grid_array[i])

plt.axis([-5, 5, -5 ,5])
plt.grid(b=True, which='both', axis='both')
plt.xlabel('X1')
plt.ylabel('X2')

for k in range(0, MAX_COUNT):
    if(grid_array[k] == 1):       
        plt.scatter(x1_array[k], x2_array[k])

plt.show()

File.close()
