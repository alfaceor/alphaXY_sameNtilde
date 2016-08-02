#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt


data=np.loadtxt("Alpha_T__Kappa.dat")

x=data[:,0]
y=data[:,1]
z=data[:,2]
colors=(z+2)/((z+2).max())
print len(x), len(y)
#plt.plot(x,y, s=np.ones(len(x)), c=colors)
plt.scatter(x,y, s=100, c=colors)
plt.show()

