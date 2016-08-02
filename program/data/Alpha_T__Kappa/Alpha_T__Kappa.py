#!/usr/bin/python
# fit a power law exponent and get the exponent
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def fit_PowerLaw(x, mm, A):
  return A*(x**mm)

def fit_Linear(x, mm,A):
  return mm*x +A

strNpart=["5", "7", "10", "14", "20", "30", "50", "100", "200"]
#strTS=["0.005625_0.004375", 
#"0.01125_0.00875", 
#"0.0225_0.0175", 
#"0.045_0.035", 
#"0.09_0.07", 
#"0.18_0.14", 
#"0.45_0.35", 
#"0.5625_0.4375",
#"0.675_0.525", 
#"0.7875_0.6125", 
#"0.90_0.70", 
#"0.99_0.77",
#"1.0125_0.7875",
#"1.125_0.875", 
#"1.2375_0.9625",
#"1.35_1.05", 
#"1.6875_1.3125",
#"1.80_1.40", 
#"2.025_1.575",
#"2.25_1.75", "6.75_5.25"]

strTS=["0.1125_0.0875",
"0.225_0.175",
"0.3375_0.2625",
"0.45_0.35",
"0.5625_0.4375",
"0.675_0.525",
"0.7875_0.6125",
"0.9_0.7",
"1.0125_0.7875",
"1.125_0.875",
"1.2375_0.9625",
"1.35_1.05",
"1.4625_1.1375",
"1.575_1.225",
"1.6875_1.3125",
"1.8_1.4",
"1.9125_1.4875",
"2.025_1.575",
"2.1375_1.6625",
]

strAlpha=["0.00", "0.25", "0.50", "0.75", "1.00", "1.25", "1.50", "1.75", "2.00","2.25", "2.50", "2.75", "3.00", "4.00", "INFT"]
#strAlpha=["2.25", "2.50"]
#strAlpha=["2.00"] #, "INFT"]

delta=0.2
zeroLimUp=delta
zeroLimDown=-delta

outFilename="Alpha_T__Kappa.dat"
ofile=open(outFilename,"w")
header="#T alpha signPwLw PwLwExpnt K0 ndatos \n"
ofile.write(header)



for mn in range(len(strNpart)):
  removeBorder=3*int(strNpart[mn])/10
  line=""
  line=line+strNpart[mn]+" "
for ms in range(len(strTS)):
  strT1=strTS[ms].split("_")[0]
  strT2=strTS[ms].split("_")[1]
  T1=float(strT1)
  T2=float(strT2)
  Tm=0.5*(T1+T2)
  DT=T1-T2 
  strTm=str(Tm)
  for ma in range(len(strAlpha)):
    X=[]
    Y=[]
    for mn in range(len(strNpart)):
      removeBorder=3*int(strNpart[mn])/10
      filename="../TempFluxProfile__N_"+strNpart[mn]+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha[ma]+".DAT"
      try:
        #data=np.loadtxt(filename,usecols=(3,))
        #J = data[:,3]
        J=np.loadtxt(filename,usecols=(3,))
        Npart = int(strNpart[mn])
        Jmean = J[removeBorder:-removeBorder].mean()
        Kappa = Npart*Jmean/DT
        X.append(Npart)
        Y.append(Kappa)
      except:
        pass
    # Now fit X Y
    #print X
    #print Y
    try:
      #params = curve_fit(fit_PowerLaw,X,Y)
      params = curve_fit(fit_Linear,np.log(X),np.log(Y))
      PwLwExpnnt=params[0][0]
      if PwLwExpnnt > zeroLimUp :
        value  = 1
        letter = "I"
      elif PwLwExpnnt < zeroLimDown:
        value  = -1
        letter = "N"
      else :
        value  = 0
        letter = "F"
      K0=params[0][1]
      #line=""+strTm+" "+strAlpha[ma]+" "+str(PwLwExpnnt)+" "+str(K0)+" "+str(len(Y))+"\n"
      if strAlpha[ma] == "INFT":
        line=""+strTm+" "+"4.00"+" "+str(value)+" "+letter+ "\n" #+str(PwLwExpnnt)+" "+str(K0)+" "+str(len(Y))+"\n"
      else:
        line=""+strTm+" "+strAlpha[ma]+" "+str(value)+" "+letter+ "\n" #+str(PwLwExpnnt)+" "+str(K0)+" "+str(len(Y))+"\n"
      ofile.write(line)
      #if Tm == 6 :
      #  if strAlpha[ma]=="1.50" :
      #print strTS[ms], strAlpha[ma]
      #plt.plot(X,Y,'-o',label=strAlpha[ma])
      #plt.plot(X,Y,'-o',label=strTS[ms])
      #plt.plot(X,fit_PowerLaw(X, PwLwExpnnt, K0), label=strAlpha[ma])
    except:
      pass
    
  #ofile.write("\n")
#plt.legend()
#plt.show()
footer="#\delta = "+str(delta)+"\n"
ofile.write(footer)
ofile.close()


