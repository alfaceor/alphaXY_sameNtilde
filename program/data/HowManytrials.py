#!/usr/bin/python
import numpy as np

strNpart=["5", "7", "10", "14", "20", "30", "50", "100", "200", "400", "800"]
strNpart=["100", "200", "400", "800"]
strNpart=["200"]
#strTS=["0.0225_0.0175", "0.045_0.035", "0.09_0.07", "0.18_0.14", "0.45_0.35", "0.675_0.525", "0.90_0.70", "0.99_0.77", "1.35_1.05", "2.25_1.75"]
strTS=["0.90_0.70"]
strAlpha=["0.00", "0.25", "0.50", "0.75", "1.00", "1.25", "1.50", "1.75", "2.00", "2.25", "2.50", "3.00", "4.00", "INFT"]
strAlpha=["1.25"]
iniJob=1
endJob=200
job_id=range(iniJob,endJob+1)
strJobID=[str(i).zfill(5) for i in job_id]


Messages=""
for mn in range(len(strNpart)):
  Messages=Messages+"\n"
  Messages=Messages+"### Npart = "+strNpart[mn]+"\n"
  for ms in range(len(strTS)):
    strT1=strTS[ms].split("_")[0]
    strT2=strTS[ms].split("_")[1]
    for ma in range(len(strAlpha)):
      count = 0
      countBad = 0
      badfiles=""
      for mj in range(len(strJobID)):
        filename="N_"+strNpart[mn]+"__FrBC__T1_"+strT1+"__T2_"+strT2+"/TempFluxI__N_"+strNpart[mn]+"__A_"+strAlpha[ma]+"__j_"+strJobID[mj]+".dat"
        try:
          data=np.loadtxt(filename)
          if len(data) == int(strNpart[mn]):
            count=count+1
          else:
            badfiles=badfiles+","+strJobID[mj]
            countBad=countBad+1
        except:
          pass
      Messages=Messages+strNpart[mn]+" "+strT1+" "+strT2+" "+strAlpha[ma]+" count = "+str(count)+" countBad = "+str(countBad)+" bad:"+badfiles+"\n"

print Messages
#N_10__FrBC__T1_0.90__T2_0.70/MicroState__N_10__A_2.50__j_00002.end
#N_10__FrBC__T1_0.90__T2_0.70/TempFluxI__N_10__A_3.75__j_00007.dat
