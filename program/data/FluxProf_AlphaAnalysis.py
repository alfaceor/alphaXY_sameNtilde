#!/usr/bin/python

strNpart="100"
strT1="0.90"
strT2="0.70"

Npart=int(strNpart)

alphaList=["0.00", "0.25", "0.50", "0.75", "1.00", "1.25", "1.50", "1.75", "2.00", "2.25", "2.50", "2.75", "3.00", "3.25", "3.50", "3.75", "4.00", "INFT"]
#alphaList=["0.00", "0.50", "1.00", "1.50", "2.00", "3.00", "INFT"]
import numpy as np

print "#Npart T1 T2 alpha fluxL[1] fluxL[Npart/2] fluxL[Npart-1], fluxR[Npart-2], fluxR[Npart/2], fluxR[0]"
for ma in range(len(alphaList)):
  #strAlpha="0.00"
  strAlpha=alphaList[ma]
  filename="TempFluxProfile__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha+".DAT"
  data=np.loadtxt(filename)
  fluxL=data[:,3]
  fluxR=data[:,5]
  print strNpart, strT1, strT2, strAlpha, fluxL[1], fluxL[Npart/2], fluxL[Npart-1], fluxR[Npart-2], fluxR[Npart/2], fluxR[0]

