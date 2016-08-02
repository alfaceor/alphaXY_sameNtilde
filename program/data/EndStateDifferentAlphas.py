#!/usr/bin/python
#@alfaceor
# Energy Plot

import numpy as np
import matplotlib.pyplot as plt

import matplotlib

from matplotlib.collections import PatchCollection
#from matplotlib.patches import Circle


# Plot parameters
font = {'family' : 'normal',
         'weight' : 'bold',
         'size'   : 30}
plt.rc('font', **font)
plt.rc('text', usetex=True)

fig1 = plt.figure()
ax1_1 = fig1.add_subplot(111)

# Options
from optparse import OptionParser
parser = OptionParser("usage:  %prog [options] arg1 ")
#parser.add_option("-k", "--kmcolumn", dest="kmcolumn")

(options, args) = parser.parse_args()

Mfiles=len(args)
inputFilename=args

#data=np.loadtxt(inputFilename[m])
yticks_alpha=["0.00", "0.25", "0.50"]
yticks_alpha=["0.00", "0.25", "0.50"]
if (len(inputFilename) == 1):
  # Is good
  data=np.loadtxt(inputFilename[0])
  print data
  lenData=len(data)
  for ii in range(lenData):
    Naux=len(data[ii])
    Npart=(Naux-1)/2
    print Naux,Npart
    ttime=data[ii,0]
    vel=data[ii,1:Naux:2]
    pos=data[ii,2:Naux:2]
    X=np.array(range(Npart))
    Y=2*ii*np.ones(len(pos))
    
    vec_m = np.zeros(len(pos)*2).reshape(len(pos),2)
    vec_m[:,0]=np.cos(pos)
    vec_m[:,1]=np.sin(pos)
    #del data
    
  
    patches = []
    for i in range(Npart):
      circle=plt.Circle((X[i], Y[i]), 0.5) #, color='r', alpha=0.5)
      patches.append(circle)
  
    p = PatchCollection(patches, cmap=matplotlib.cm.RdBu)#, alpha=0.4)
    p.set_clim(-2.0, 2.0)
    p.set_array(vel)
    ax1_1.add_collection(p)
  
    ax1_1.set_aspect('equal')
    ax1_1.quiver( X, Y, vec_m[:,0], vec_m[:,1],  color='k', pivot='mid', alpha=0.8, units='xy', width=0.1, scale=1.0)
    ax1_1.quiver( X, Y, vec_m[:,0], vec_m[:,1],  color='k', pivot='mid', alpha=0.8, units='xy', width=0.1, scale=1.0)
    
    
    print vec_m.mean(axis=0)
  
  #ax1_1.set_yticks(yticksAlpha, ylabelsAlpha)
  ax1_1.set_yticks([])
  ax1_1.set_xlim(-1,Npart)
  ax1_1.set_ylim(-1,lenData+1)
  ax1_1.set_xlabel("$i$")
  ax1_1.set_ylabel("$\\alpha$")
  
  fig1.subplots_adjust(right=0.8)
  cbar_ax = fig1.add_axes([0.85, 0.15, 0.05, 0.7])
  fig1.colorbar(p, cax=cbar_ax) #, orientation="horizontal")
  #fig1.tight_layout()
  plt.show()
