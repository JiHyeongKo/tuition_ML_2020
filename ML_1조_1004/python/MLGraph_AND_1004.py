import matplotlib.pyplot as plt
import numpy as np
import sys

andLineFile = open('AND_line_data.txt', 'r', encoding = 'utf-8')
data = andLineFile.readline()

#while True:
a_line = andLineFile.readline()
b_line = andLineFile.readline()
c_line = andLineFile.readline()

a =float(a_line.rstrip('\n'))
b =float(b_line.rstrip('\n'))
c =float(c_line.rstrip('\n'))

x1 = np.arange(0, 2.1, 0.1)
x2 = (-a/b)*x1 + (c/b)

plt.plot(x1, x2)
plt.grid()
plt.xlabel('x1')
plt.ylabel('x2')
title = str(a)+ ' * x1 +' +str(b)+ ' * x2 = ' +str(c)
plt.title(title)
plt.show()
andLineFile.close()

andDotLineFile = open('AND_dot_line_data.txt', 'r', encoding = 'utf-8')
MAX_COUNT=len(andDotLineFile.readlines())-1
andDotLineFile.seek(0)

data = andDotLineFile.readline()

w1=[]
w2=[]

for i in range (MAX_COUNT):
	w1.append(0)
	w2.append(0)
	
for k in range(0, MAX_COUNT, 1):
	w1_buffer = andDotLineFile.read(8)
	space = andDotLineFile.read(1)
	w2_buffer = andDotLineFile.read(8)
	enter = andDotLineFile.readline()
	w1[k] = w1_buffer
	w2[k] = w2_buffer

for i in range(1, MAX_COUNT, 1):
    if w1[i] == '0.000000':
        w1[i]=w1[i-1]
    if w2[i] == '0.000000':
        w2[i]=w2[i-1]

plt.scatter(w1, w2)
plt.grid()
plt.xlabel('w1')
plt.ylabel('w2')
title = ''
plt.title(title)
plt.show()
andDotLineFile.close()
