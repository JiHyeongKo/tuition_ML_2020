import matplotlib.pyplot as plt
import numpy as np
import sys

MyFile = open('line_data.txt', 'r', encoding = 'utf-8')   
data = MyFile.readline()

#while True:
a_line = MyFile.readline()
b_line = MyFile.readline()
c_line = MyFile.readline()

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

MyFile.close()
