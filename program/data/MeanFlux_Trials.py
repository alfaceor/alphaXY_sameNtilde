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
  outFilename = "NJ__A_VAR__trials.DAT"
else:
  outFilename = options.outFilename

if (options.removeBorder == None ):
  removeBorder = 4
else:
  removeBorder = int(options.removeBorder)



#N_400__FrBC__T1_0.90__T2_0.70/TempFluxI__N_400__A_0.00__j_000
strNpart=["50"]
strTS=["0.90_0.70"]
strAlpha=["0.00", "0.25", "0.50", "0.75", "1.00", "1.25"]


#-------------------------------


fileHeader="#id"
for ma in range(len(strAlpha)):
  fileHeader=fileHeader+" "+strAlpha[ma]
fileHeader=fileHeader+"\n"


print fileHeader
for mn in range(len(strNpart)):
  auxvar=3*int(strNpart[mn])/10
  print auxvar
  for ms in range(len(strTS)):
    strT1=strTS[ms].split("_")[0]
    strT2=strTS[ms].split("_")[1]
    # outfilename
    outFilename="NJ__N_"+strNpart[mn]+"__T1_"+strT1+"__T2_"+strT2+"__A_VAR__trials.DAT"
    outFile=open(outFilename,'w')
    outFile.write("# "+outFilename+"\n")
    outFile.write(fileHeader) 
    for mi in range(20):
      strJobID=str(mi).zfill(5)
      print strJobID
      line=strJobID+" "
      for ma in range(len(strAlpha)):
        try:
          filename="N_"+strNpart[mn]+"__FrBC__T1_"+strT1+"__T2_"+strT2+"/TempFluxI__N_"+strNpart[mn]+"__A_"+strAlpha[ma]+"__j_"+strJobID+".dat"
          data=np.loadtxt(filename)
          X = data[:,0]
          T = data[:,1]
          J = data[:,2]
          NJmean = float(strNpart[mn])*J[auxvar:-auxvar].mean()
          line=line+str(NJmean)+" "
        except : #IOError as e: 
          line=line+"NaN "
      line=line+"\n"
      outFile.write(line)
    outFile.close()
    print outFilename


          


      
#
##filename="N_400__FrBC__T1_0.90__T2_0.70/TempFluxI__N_400__A_0.00__j_000*.dat"
#
#fileHeader="#Npart alpha T1 T2 slope slope_std flux flux_std flux/slope kappa\n"
#
#outFile = open(outFilename, 'w')
#outFile.write(fileHeader)
#
#auxvar=removeBorder
#
#for i in range(Mfiles):
#  try:
#    data=np.loadtxt(filename[i])
#    baseName = os.path.splitext(filename[i])[0]
#    #strNpart = baseName.split("__")[1].split("_")[1]
#    #strT1    = baseName.split("__")[2].split("_")[1]
#    #strT2    = baseName.split("__")[3].split("_")[1]
#    #strAlpha = baseName.split("__")[4].split("_")[1]
#    #strID    = baseName.split("__")[5].split("_")[1]
#    Npart = 400    
#    #Npart = int(strNpart)
#    X = data[:,0]
#    T = data[:,1]
#    J = data[:,2]
#    params = curve_fit(fit_line,X[auxvar:-auxvar],T[auxvar:-auxvar])
#    slope_mean = params[0][0]
#    slope_std  = np.sqrt(params[1][0][0])
#    Jmean = J[auxvar:-auxvar].mean()
#    Jstd  = J[auxvar:-auxvar].std()
#    #print strNpart, strT1, strT2, strID, strAlpha, Jmean, Jstd
#    print Npart*Jmean
#    #JoverSlope=Jmean/slope_mean
#    #DeltaT=float(strT2)-float(strT1)
#    #kappa=-Jmean*Npart/DeltaT
#    #outFile.write(strNpart+" "+strAlpha+" "+strT1+" "+strT2+" "+str(slope_mean)+" "+str(slope_std)+" "+str(Jmean)+" "+str(Jstd)+" "+str(JoverSlope)+" "+str(kappa)+"\n")
#  except IOError as e:
#    print "error :"
#
#outFile.close()
#print outFilename








