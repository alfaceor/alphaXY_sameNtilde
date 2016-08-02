#!/usr/bin/python
#strNpart=["5", "7", "10", "14", "30"]
strNpart=["200"]
for mn in range(len(strNpart)):
  for i in range(20):
    T=0.1*(i+1)
    halfDeltaT=T/8.0
    T1=T+halfDeltaT
    T2=T-halfDeltaT
    #print T, T1, T2
    #print "\""+str(T1)+"_"+str(T2)+"\", # "+str(T)
    #print "T="+str(T)+";"+"./execute_cluster_jobs.sh 200 "+str(T1)+" "+str(T2)   #+"  # T = "+str(T)
    #print "./rsync_cluster_data.sh "+strNpart[mn]+" "+str(T1)+" "+str(T2) #+" # "+str(T)
    print "./GetTempFluxProfile.sh "+strNpart[mn]+" "+str(T1)+" "+str(T2) #+" # "+str(T)
    #print "gnuplot -e \"strT1='"+str(T1)+"'\" -e \"strT2='"+str(T2)+"'\" Npart_vs_NJ__T1_arg1__T2_arg2__A_VAR_cols.plt"
    #print str(T)

