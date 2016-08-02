#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <limits>

#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "IOParams.h"
#include "Chain.h"
#include "HeatBath.h"
#include "TimeStats.h"

#define indx(i,j,DIM) (((i)*DIM)+j)
using namespace std;
typedef std::numeric_limits< double > dbl;

int main(int argc, char **argv){
  // Initiate objects.
  cout<< "mainAlphaXY_FNB"<<endl;
  IOParams io(argc, argv);
  
  Chain ch_o(io.N, io.alpha, io.k, io.kp);
  
        ch_o.kpL=io.kp; ch_o.kpR=io.kp;
        ch_o.dt= io.dt; ch_o.dt2= io.dt2;
  Chain ch_n(io.N, io.alpha, io.k, io.kp);

        ch_n.kpL=io.kp; ch_n.kpR=io.kp;
        ch_n.dt= io.dt; ch_n.dt2= io.dt2;
        cout << ch_o.k << " " <<ch_n.k <<endl;
  
  HeatBath hbL(1.00, io.gamma1, io.T1, io.dt, io.dt2, io.seed01_1, io.seed01_2);
  HeatBath hbR(1.00, io.gamma2, io.T2, io.dt, io.dt2, io.seed02_1, io.seed02_2);
  
  TimeStats ts(io.N);
  
  double tt=io.ttime*io.dt;
  
  // Files to save data.
  io.strAlpha="INFT";
  string   flnBase="__N_"+io.strN+"__A_"+io.strAlpha+"__j_"+io.strJob_id;
  
  // Temperature profile calculated with time mean.
  string   flnTempFluxI = "TempFluxI"+flnBase+".dat";
  string   hdrTempFluxI = "#i T_i JL_i JR_i";
  ofstream ofileTempFluxI; 
  ofileTempFluxI.open(flnTempFluxI.c_str()); 
  ofileTempFluxI << hdrTempFluxI<<endl;
  
  // Energy data
  string   flnNrg = "Nrg"+flnBase+".dat";
  string   hdrNrg = "#t Et Ek Ep JL";
  ofstream ofileNrg; 
  ofileNrg.open(flnNrg.c_str()); 
  ofileNrg << hdrNrg <<endl;
  
  // Energy data time Mean tmp
  string   flnNrgMeanTmp = "NrgMeanTmp"+flnBase+".dat";
  string   hdrNrgMeanTmp = "#t Et Et2 Ek Ek2 Ep Ep2 JL JL2 JR JR2";
  ofstream ofileNrgMeanTmp; 
  ofileNrgMeanTmp.open(flnNrgMeanTmp.c_str()); 
  ofileNrgMeanTmp << hdrNrg <<endl;
  
  
  // Magnetization
  string   flnPositionsMagne = "PositionsMagne"+flnBase+".dat";
  string   hdrPositionsMagne = "#t __q[i]___ Mx My M";
  ofstream ofilePositionsMagne; 
  ofilePositionsMagne.open(flnPositionsMagne.c_str()); 
  ofilePositionsMagne << hdrPositionsMagne <<endl;

  // Initial conditions
  ch_o.waterBag(io.seedini, io.p0, M_PI/2.0);
  ch_n.waterBag(io.seedini, io.p0, M_PI/2.0);
  
  //Calculate Forces.
  ch_o.calcForcesFNBdump3();
  ch_n.calcForcesFNBdump3();
  
  // TRANSIENT DYNAMICS
  io.ttime=0;
  int tTransient=0;
  while (io.ttime < tTransient){
    if (io.ttime%2 == 0)
      ch_o.MolecularDynamicsHBsFNB(&ch_n, &hbL, &hbR);
    else
      ch_n.MolecularDynamicsHBsFNB(&ch_o, &hbL, &hbR);
    io.ttime++;
  }

  // STATIONARY STATE
  io.ttime=0;
  ch_o.calcForcesFNBdump3();
  while (io.ttime < io.timeSteps){
    if (io.ttime%2 == 0)
      ch_o.MolecularDynamicsHBsFNB(&ch_n, &hbL, &hbR);
    else
      ch_n.MolecularDynamicsHBsFNB(&ch_o, &hbL, &hbR);
    
    if (io.ttime % io.taux == 0 ){
      tt=io.ttime*io.dt;
      ch_o.calcEk_i();
      ch_o.calcEp_i2();
      ch_o.calcFluxFNB02();
      
      ofilePositionsMagne<<ch_o.strPositionsMagne(tt);
      
      ofileNrg << ch_o.strNrgTot(tt);
      
      ts.add(&ch_o);
      ofileNrgMeanTmp<<ts.strEnergMeanTmp(tt);
      
    }
    io.ttime++;
  }
  ofilePositionsMagne.close();
  cout<< ch_o.strPhaseSpace(tt);
  ofileNrgMeanTmp.close();

  ts.getTimeMean();  

  ofileTempFluxI << ts.strTempFluxI();
  ofileTempFluxI << io.getParams();
  ofileTempFluxI << hbL.getParams();
  ofileTempFluxI << ts.strEnergyMean(ch_o.alpha, ch_o.NtildeTot);
  ofileTempFluxI.close();
  
  ofileNrg << ts.strEnergyMean(ch_o.alpha, ch_o.NtildeTot);
  ofileNrg.close();
  
  string   flnEND = "MicroState"+flnBase+".end";
  ofstream ofileEND; ofileEND.open(flnEND.c_str()); 
  ofileEND << ch_o.strMicroState(tt) <<endl;
  ofileEND << "#t";
  for (int i=0; i<io.N; i++) ofileEND << " p_" << i<<" q_" << i;
  ofileEND << endl;
  ofileEND << io.getParams();
  ofileEND << hbL.getParams();
  ofileEND << hbR.getParams();
  ofileEND << ch_o.getParams();
  ofileEND << ts.strEnergyMean(ch_o.alpha, ch_o.NtildeTot);
  ofileEND.close();
  
  }




//  string   flnINI = "Microstate"+flnBase+".ini";
//  string   hdrINI = "#Phase space and initial forces";
//  ofstream ofileINI; 
//  ofileINI.open(flnINI.c_str()); 
//  ofileINI << hdrINI<<endl;
//  ofileINI << ch_o.strPhaseSpace(io.dt*io.ttime);
//  ofileINI << "------------" <<endl;
//  ofileINI << ch_o.strForce(io.ttime*io.dt);
//  ofileINI.close();