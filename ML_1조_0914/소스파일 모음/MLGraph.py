import matplotlib.pyplot as plt
import numpy as np
import sys

MyFile = open('line_data.txt', 'r', encoding = 'utf-8')   
data = MyFile.readline()

#while True:
m_line = MyFile.readline()
n_line = MyFile.readline()
m =float(m_line.rstrip('\n'))
n =float(n_line.rstrip('\n'))

x1 = np.arange(-1, 1.1, 0.1)
x2 = (m*x1+n)

plt.plot(x1, x2)
plt.grid()
plt.xlabel('x1')
plt.ylabel('x2')
title = 'x2 = '+str(m)+' x1+'+str(n)
plt.title(title)
plt.show()

MyFile.close()
