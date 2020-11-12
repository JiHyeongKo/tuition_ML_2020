import matplotlib.pyplot as plt
import numpy as np
import sys
MAX_COUNT = 1000
    
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

for i in range(1, MAX_COUNT, 1):
    if ( x1_array[i] == '') or (x1_array[i] == '\n'):
        x1_array[i]=x1_array[i-1]
    if ( x2_array[i] == '') or (x2_array[i] == '\n'):
        x2_array[i]=x2_array[i-1]
    if ( t[i] == '') or (t[i] == '\n'):
        t[i]=t[i-1]

for i in range(0, MAX_COUNT, 1):
    x1_array[i] = float(x1_array[i])
    x2_array[i] = float(x2_array[i])
    t[i] = float(t[i])


plt.axis([-5, 5, -5 ,5])
plt.grid(b=True, which='both', axis='both')
plt.xlabel('x1')
plt.ylabel('x2')

for i in range(0, MAX_COUNT, 1):
	if(t[i] == 1):
		plt.scatter(x1_array[i], x2_array[i], color='0.75', edgecolor="b")
	else:
		plt.scatter(x1_array[i], x2_array[i], color='1', edgecolor="r")
		 
       

plt.show()

File.close()
