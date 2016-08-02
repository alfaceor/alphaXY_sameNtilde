#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

strNpart="100"
strAlpha=["0.00", "0.50", "1.00", "1.50", "1.75", "2.00","2.25", "2.50", "3.00", "3.50", "4.00", "INFT"]
strTS=["0.50_0.30", "0.70_0.50", "0.90_0.70"]
#DiffFromReservatory_to_secondParticle__N_100__VAR_ALPHA_
#BoundaryResistance__N_100__VAR_ALPHA

for mt in range(len(strTS)):
  #"TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.00.DAT"
  strT1=strTS[mt].split("_")[0]
  strT2=strTS[mt].split("_")[1]
  outfilename01="BoundarResistance__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__VAR_ALPHA.DAT"
  outfilename02="Jumps__T_1_to_T_2__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__VAR_ALPHA.DAT"
  outfilename03="Jumps__Rsr_to_T_2__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__VAR_ALPHA.DAT"
  hdrfilename="#Npart T1 T2 alpha jumpL jumpR\n"
  ofile01=open(outfilename01,'w')
  ofile02=open(outfilename02,'w')
  ofile03=open(outfilename03,'w')
  ofile01.write(hdrfilename)
  ofile02.write(hdrfilename)
  ofile03.write(hdrfilename)
  for ma in range(len(strAlpha)):
    filename="TempFluxProfile__N_"+strNpart+"__T1_"+strT1+"__T2_"+strT2+"__A_"+strAlpha[ma]+".DAT"
    try:
      data=np.loadtxt(filename)
      # ofile01 Boundary Resistance
      jumpL=float(strT1)-data[0,1]
      jumpR=data[len(data)-1,1]- float(strT2) 
      line=strNpart+" "+strT1+" "+strT2+" "+strAlpha[ma]+" "+str(jumpL)+" "+str(jumpR)+"\n"
      ofile01.write(line)
      # ofile02 Jump from particle T_1 to particle T_2
      jumpL=data[0,1]-data[1,1]
      jumpR=data[len(data)-2,1]- data[len(data)-1,1]   #data[len(data)-1,1]
      line=strNpart+" "+strT1+" "+strT2+" "+strAlpha[ma]+" "+str(jumpL)+" "+str(jumpR)+"\n"
      ofile02.write(line)
      # ofile02 Jump from particle T_1 to particle T_2
      jumpL=float(strT1)-data[1,1]
      jumpR=data[len(data)-2,1]- float(strT2)
      line=strNpart+" "+strT1+" "+strT2+" "+strAlpha[ma]+" "+str(jumpL)+" "+str(jumpR)+"\n"
      ofile03.write(line)
    except IOError as e:
      print "There is no "+filename

  ofile01.close()
  ofile02.close()
  ofile03.close()
#plt.show()
