import matplotlib.pyplot as plt
import numpy as np
import sys
MAX_COUNT = 100

File = open('write_data.txt', 'r', encoding = 'utf-8')
data = File.readline()

x1_array=[]
x2_array=[]
t=[]
y=[]

for i in range(0, MAX_COUNT, 1):
    x1_array.append(0)
    x2_array.append(0)
    t.append(0)
    y.append(0)
    

for k in range(0, MAX_COUNT, 1):
    lineBuffer = File.readline()
    line = (lineBuffer.rstrip('\t'))
    x1_buffer = line[0:9]
    x2_buffer = line[10:19]
    t_buffer = line[20:29]
    y_buffer = line[30:39]
    x1_array[k] = x1_buffer
    x2_array[k] = x2_buffer
    t[k] = t_buffer
    y[k] = y_buffer
    enter = File.readline()
    
print (x1_array)
print (x2_array)
x_axis = np.arange(-5, 5.1, 0.1)
y_axis = np.arange(-5, 5.1, 0.1)

plt.plot(x_axis, y_axis)
plt.grid()
plt.xlabel('x1')
plt.ylabel('x2')
plt.scatter(x1_array, x2_array)
plt.show()

File.close()
