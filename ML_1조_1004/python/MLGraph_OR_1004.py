import matplotlib.pyplot as plt
import numpy as np
import sys

orLineFile = open('OR_line_data.txt', 'r', encoding = 'utf-8')
data = orLineFile.readline()

#while True:
a_line = orLineFile.readline()
b_line = orLineFile.readline()
c_line = orLineFile.readline()

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
orLineFile.close()

MAX_COUNT=100

orDotLineFile = open('OR_dot_line_data.txt', 'r', encoding = 'utf-8')

MAX_COUNT=len(orDotLineFile.readlines())-1
orDotLineFile.seek(0)

data = orDotLineFile.readline()

w1=[]
w2=[]

for i in range (MAX_COUNT):
	w1.append(0)
	w2.append(0)
 
for k in range(0, MAX_COUNT, 1):
	w1_buffer = orDotLineFile.read(8)
	space = orDotLineFile.read(1)
	w2_buffer = orDotLineFile.read(8)
	enter = orDotLineFile.readline()
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
