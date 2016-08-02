#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

from optparse import OptionParser

parser=OptionParser("usage: %prog")

parser.add_option("-N", "--Npart", dest="strNpart")
parser.add_option("-A", "--alpha", dest="strAlpha")
parser.add_option("-j", "--jobID", dest="strJobID")
parser.add_option("-x", "--xcol", dest="xcol")
parser.add_option("-y", "--ycol", dest="ycol")
parser.add_option("-1", "--T1", dest="T1")
parser.add_option("-2", "--T2", dest="T2")
parser.add_option("-S", "--TS", dest="TS")

(options, args) = parser.parse_args();

if options.strNpart==None:
  strNpart="50"
else:
  strNpart=options.strNpart
strNpart=strNpart.split(",")
mNpart=len(strNpart)

if options.strAlpha==None:
  strAlpha="0.00"
else:
  strAlpha=options.strAlpha
strAlpha=strAlpha.split(",")
mAlpha=len(strAlpha)

if options.strJobID==None:
  strJobID="00001"
else:
  strJobID=options.strJobID
  if strJobID.find("-") == -1:
    auxJobID=strJobID.split(",")
    strJobID=[auxJobID[i].zfill(5) for i in range(len(auxJobID))]
    print strJobID
    mJobID=len(strJobID)
  else:
    strJobID=strJobID.split("-")
    strJobID=[str(i).zfill(5) for i in range(int(strJobID[0]),int(strJobID[1])+1)]
    mJobID=len(strJobID)
    print strJobID

if options.xcol == None:
  xcol = 0
else:
  xcol = int(options.xcol)

if options.ycol == None:
  ycol = 1
else:
  ycol = int(options.ycol)

if options.T1 == None:
  strT1 = "0.90"
else:
  strT1 = options.T1

if options.T2 == None:
  strT2 = "0.70"
else:
  strT2 = options.T2

if options.TS == None:
  strTS = "0.90_0.70"
else:
  strTS = options.TS
strTS=strTS.split(",")
mTS=len(strTS)


aux=120
colores=['red', 'blue', 'black']
for mn in range(mNpart):
  for ma in range(mAlpha):
    for mj in range(mJobID):
      for mts in range(mTS):
        strT1=strTS[mts].split("_")[0]
        strT2=strTS[mts].split("_")[1]
        dirname="N_"+strNpart[mn]+"__FrBC__T1_"+strT1+"__T2_"+strT2
        filename="TempFluxI__N_"+strNpart[mn]+"__A_"+strAlpha[ma]+"__j_"+strJobID[mj]+".dat"
        datfilename=dirname+"/"+filename
        try:
          print datfilename
          data=np.loadtxt(datfilename)
          etiqueta="N_"+strNpart[mn]+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha[ma]+"__j_"+strJobID[mj]+" "+ str(data[:, ycol].mean())+"  "+str(data[aux:-aux, ycol].mean())
          #plt.plot(data[:, xcol], data[:, ycol], label="N_"+strNpart[mn]+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha[ma]+"__j_"+strJobID[mj]) #, color=colores[ma])
          plt.plot(data[:, xcol]/(float(strNpart[mn])-1), data[:, ycol], label=etiqueta) #, color=colores[ma])
          plt.legend(loc='best',prop={'size':8})
        except Exception as e:
          print e

#plt.ylim(float(strT2),float(strT1))
plt.show()

