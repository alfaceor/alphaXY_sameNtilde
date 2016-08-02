#!/usr/bin/python

strNpart="100"
strRemov=str(int(0.3*int(strNpart)))
alphaList=["0.00", "0.50", "1.00", "1.50", "2.00", "3.00", "INFT"]
TempList=["0.40_0.20", "0.50_0.30", "0.60_0.40", "0.70_0.50", "0.80_0.60", "0.90_0.70", "1.30_1.10", "1.90_1.70", "2.50_2.30"]

files2GetSlope_Flux=""
for ma in range(len(alphaList)):
  files2GetSlope_Flux=""
  for tm in range(len(TempList)):
    strT1=TempList[tm].split("_")[0]
    strT2=TempList[tm].split("_")[1]
    strAlpha=alphaList[ma]
    files2GetSlope_Flux=files2GetSlope_Flux+"TempFluxProfile__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha+".DAT"+" "
    #print alphaList[ma],TempList[tm]
  #print files2GetSlope_Flux
  print "./GetSlope_Flux.py "+files2GetSlope_Flux+" -r "+strRemov+" -o KAPPA_T__N_"+strNpart+"__A_"+strAlpha+".DAT"
#./GetSlope_Flux.py TempFluxProfile__N_100__T1_*__T2_*__A_${alpha}.DAT  -r 30 -o KAPPA_T__N_100__A_${alpha}.DAT

