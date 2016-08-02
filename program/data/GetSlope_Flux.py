#!/usr/bin/python
"""
Input: alphas to construct the following table
Npart U0 T1 T2 alpha slope slope_std flux flux_std
"""
def fit_line(x, m, b):
    return m*x + b

import numpy as np
from scipy.optimize import curve_fit
from optparse import OptionParser
import os.path

parser = OptionParser("usage: %prog [options] alphas ")
parser.add_option("-o", "--outFilename", dest="outFilename")
parser.add_option("-r", "--removeBorder", dest="removeBorder")

(options, args) = parser.parse_args()

filename=args
Mfiles=len(filename)

if (options.outFilename == None ):
  outFilename = "SLOPE_FLUX.DAT"
else:
  outFilename = options.outFilename

if (options.removeBorder == None ):
  removeBorder = 4
else:
  removeBorder = int(options.removeBorder)


#-------------------------------

fileHeader="#Npart alpha T1 T2 slope slope_std flux flux_std flux/slope kappa\n"

outFile = open(outFilename, 'w')
outFile.write(fileHeader)

auxvar=removeBorder

for i in range(Mfiles):
  try:
    data=np.loadtxt(filename[i])
    baseName = os.path.splitext(filename[i])[0]
    strNpart = baseName.split("__")[1].split("_")[1]
    strT1    = baseName.split("__")[2].split("_")[1]
    strT2    = baseName.split("__")[3].split("_")[1]
    strAlpha = baseName.split("__")[4].split("_")[1]
    
    Npart = int(strNpart)
    X = data[:,0]
    T = data[:,1]
    J = data[:,3]
    params = curve_fit(fit_line,X[auxvar:-auxvar],T[auxvar:-auxvar])
    slope_mean = params[0][0]
    slope_std  = np.sqrt(params[1][0][0])
    Jmean = J[auxvar:-auxvar].mean()
    Jstd  = J[auxvar:-auxvar].std()
    JoverSlope=Jmean/slope_mean
    DeltaT=float(strT2)-float(strT1)
    kappa=-Jmean*Npart/DeltaT
    outFile.write(strNpart+" "+strAlpha+" "+strT1+" "+strT2+" "+str(slope_mean)+" "+str(slope_std)+" "+str(Jmean)+" "+str(Jstd)+" "+str(JoverSlope)+" "+str(kappa)+"\n")
  except IOError as e:
    print "error :"

outFile.close()
print outFilename








