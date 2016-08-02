#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
import os.path
from optparse import OptionParser

parser = OptionParser("usage: %prog [option] <filename.dat> # to Calculate mean for trials")
parser.add_option("-o","--outFilename", dest="outFilename")

(options, args) = parser.parse_args()


filename=args
Mfiles=len(filename)

data=np.loadtxt(filename[0])
dirName = os.path.dirname(filename[0]).split("__")
strNpart= dirName[0].split("_")[1]
strT1   = dirName[2].split("_")[1]
strT2   = dirName[3].split("_")[1]
basName = os.path.basename(filename[0]).split("__")
strAlpha= basName[2].split("_")[1]
lenData=len(data)
coldat=7
dataMeanStd=np.zeros(lenData*coldat).reshape(lenData,coldat)
#strNpart=os.path.basename(filename[0]).split("__")[1].split("_")[1]
Npart=int(strNpart)

if (options.outFilename == None):
  outFilename="TempFluxProfile__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha+".DAT"
else:
	outFilename=options.outFilename


dataMeanStd[:,0] = data[:,0]/(Npart-1)
count=0;
if Mfiles == 0:
  print "No files to calculate"
else:
  for i in range(Mfiles):
    try:
      data=np.loadtxt(filename[i])
      if len(data) == lenData:
        dataMeanStd[:,1]=dataMeanStd[:,1]+data[:,1]      # T_i   mean
        dataMeanStd[:,2]=dataMeanStd[:,2]+data[:,1]**2   # T_i   variance
        dataMeanStd[:,3]=dataMeanStd[:,3]+data[:,2]      # JL_i  mean
        dataMeanStd[:,4]=dataMeanStd[:,4]+data[:,2]**2   # JL_i  variance
        dataMeanStd[:,5]=dataMeanStd[:,5]+data[:,3]      # JR_i  mean
        dataMeanStd[:,6]=dataMeanStd[:,6]+data[:,3]**2   # JR_i  variance
        count=count+1
      else:
        print 'file not complete ' + filename[i]
    except Exception as e:
      print e
    
  #print 'count='+str(count)
  # Get the mean
  dataMeanStd = dataMeanStd/count
  
  # Get standard deviation
  dataMeanStd[:,0] = dataMeanStd[:,0]*count
  dataMeanStd[:,2] = np.sqrt(dataMeanStd[:,2]-dataMeanStd[:,1]**2)
  dataMeanStd[:,4] = np.sqrt(dataMeanStd[:,4]-dataMeanStd[:,3]**2)
  dataMeanStd[:,6] = np.sqrt(dataMeanStd[:,6]-dataMeanStd[:,5]**2)
  
  np.savetxt(outFilename,dataMeanStd)
  print outFilename+'   count='+str(count)
  # Temp profile
  #plt.plot(dataMeanStd[:,0], dataMeanStd[:,1])
  #plt.plot(dataMeanStd[:,0], dataMeanStd[:,1]+0.5*dataMeanStd[:,2], '--r')
  #plt.plot(dataMeanStd[:,0], dataMeanStd[:,1]-0.5*dataMeanStd[:,2], '--r')
  
  
  # Flux profile
  #plt.plot(dataMeanStd[:,0], dataMeanStd[:,3])
  #plt.plot(dataMeanStd[:,0], dataMeanStd[:,3]+0.5*dataMeanStd[:,4], '--r')
  #plt.plot(dataMeanStd[:,0], dataMeanStd[:,3]-0.5*dataMeanStd[:,4], '--r')
  #
  #
  #plt.show()


