#!/usr/bin/python
# Check out the jobs that are  missing
import numpy as np
import os.path
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
  strJobID=strJobID.split(",")
  mJobID=len(strJobID)
else:
  strJobID=options.strJobID
  if strJobID.find("-") == -1:
    auxJobID=strJobID.split(",")
    strJobID=[auxJobID[i].zfill(5) for i in range(len(auxJobID))]
    #print strJobID
    mJobID=len(strJobID)
  else:
    strJobID=strJobID.split("-")
    strJobID=[str(i).zfill(5) for i in range(int(strJobID[0]),int(strJobID[1])+1)]
    mJobID=len(strJobID)
    #print strJobID


if options.TS == None:
  strTS = "0.90_0.70"
else:
  strTS = options.TS
strTS=strTS.split(",")
mTS=len(strTS)


#TempFluxI__N_100__A_1.00__j_00021.dat
#MicroState__N_100__A_2.00__j_00021.end
jobsWithError001=""
jobsWithError002=""
jobsWithError003=""
jobsWithError004=""
errorFiles=""
DELRERUN=""
QRUNNING=""

for mn in range(mNpart):
  for ma in range(mAlpha):
    for mj in range(mJobID):
      for mts in range(mTS):
        isDatfile=False
        isEndfile=False
        strT1=strTS[mts].split("_")[0]
        strT2=strTS[mts].split("_")[1]
        dirname="data/N_"+strNpart[mn]+"__FrBC__T1_"+strT1+"__T2_"+strT2
        filename="__N_"+strNpart[mn]+"__A_"+strAlpha[ma]+"__j_"+strJobID[mj]
        datfilename=dirname+"/"+ "TempFluxI"+filename+".dat" 
        endfilename=dirname+"/"+"MicroState"+filename+".end"
        # datfilename exist?
        isDatfile=os.path.isfile(datfilename)
        isEndfile=os.path.isfile(endfilename)
        
        if ( isDatfile and isEndfile ):
          # Check file integrity
          try:
            data=np.loadtxt(datfilename)
            Npart=int(strNpart[mn])
            if len(data) != Npart:
              #print "Is file still RUNNING?"
              jobsWithError003=jobsWithError003+strJobID[mj]+","
              # DELETE AND RERUN
              DELRERUN=DELRERUN+"rm "+datfilename+" "+endfilename+"\n"
          except Exception as e:
            # DELETE AND RERUN
            DELRERUN=DELRERUN+"rm "+datfilename+" "+endfilename+"\n"
        else:
          if ( not isEndfile ):
            if ( isDatfile ):
              # Job Still RUNNING?
              QRUNNING=QRUNNING+filename+"\n"
            else:
              # Awkward!!!
              # DELETE AND RERUN
              DELRERUN=DELRERUN+"rm "+datfilename+" "+endfilename+"\n"
          else:
            # Awkward!
            # DELETE AND RERUN
            DELRERUN=DELRERUN+"rm "+datfilename+" "+endfilename+"\n"

print "======== JOBS TO DELETE AND RERUN ======="
print DELRERUN
print "========================================="


print "******** THESE JOBS ARE RUNNING?  *******"
print QRUNNING
print "*****************************************"


#if len(jobsWithError001) != 0 :
#  print ""
#  print "---- ERROR: END FILE DOESN'T EXIST! ---- : "
#  print jobsWithError001
#  print "----------------------------------------"
#  print ""
#if len(jobsWithError002) != 0 :
#  print ""
#  print "++++ ERROR: DAT FILE DOESN'T EXIST! ++++ : "
#  print jobsWithError002
#  print "++++++++++++++++++++++++++++++++++++++++"
#  print ""
#if len(jobsWithError003) != 0 :
#  print ""
#  print "==== ERROR: METADATA DOESN'T MATCH! ==== : "
#  print jobsWithError003
#  print "========================================"
#  print ""
#if len(jobsWithError004) != 0 :
#  print ""
#  print "**** ERROR: CAN'T LOAD DATA!: **** "
#  print jobsWithError004
#  print "**********************************"
#  print ""
#
#print errorFiles

