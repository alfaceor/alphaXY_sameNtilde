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
  cout<< "mainAlphaXY_sameNtildeIncorrect"<<endl;
  IOParams io(argc, argv);
  cout << io.inifilename <<endl;
  
  Chain ch_o(io.N, io.alpha, io.k, io.kp);
        ch_o.calcInvNtildeI_divN_incorrect();  ch_o.k = ch_o.k/ch_o.NtildeTot;
        ch_o.kpL=io.kp; ch_o.kpR=io.kp;
        ch_o.dt= io.dt; ch_o.dt2= io.dt2;
  Chain ch_n(io.N, io.alpha, io.k, io.kp);
        ch_n.calcInvNtildeI_divN_incorrect();  ch_n.k = ch_n.k/ch_n.NtildeTot;
        ch_n.kpL=io.kp; ch_n.kpR=io.kp;
        ch_n.dt= io.dt; ch_n.dt2= io.dt2;
        cout << ch_o.k << " " <<ch_n.k <<endl;
  
  
  TimeStats ts(io.N);
  
  double tt=io.ttime*io.dt;
  
  // Files to save data.
  
  string   flnBase="_Incorr__N_"+io.strN+"__A_"+io.strAlpha+"__j_"+io.strJob_id;
  
  cout<<ch_o.getParams();
  // Temperature profile calculated with time mean.
  string   flnTempFluxI = "TempFluxI"+flnBase+".dat";
  string   hdrTempFluxI = "#i T_i JL_i JR_i";
  ofstream ofileTempFluxI; 
  ofileTempFluxI.open(flnTempFluxI.c_str()); 
  ofileTempFluxI << hdrTempFluxI<<endl;
  
  // Energy data
  string   flnNrg = "Nrg"+flnBase+".dat";
  string   hdrNrg = "#t Ek Ep Et JL JR";
  ofstream ofileNrg; 
  ofileNrg.open(flnNrg.c_str()); 
  ofileNrg << hdrNrg <<endl;
  
  // Energy data time Mean tmp
  string   flnNrgMeanTmp = "NrgMeanTmp"+flnBase+".dat";
  string   hdrNrgMeanTmp = "#t tcount Et_mean Et2_mean Ek_mean Ek2_mean Ep_mean Ep2_mean JL_mean JL2_mean JR_mean JR2_mean M_mean M2_mean";
  ofstream ofileNrgMeanTmp; 
  ofileNrgMeanTmp.open(flnNrgMeanTmp.c_str()); 
  ofileNrgMeanTmp << hdrNrgMeanTmp <<endl;
  
  
  // Magnetization
  string   flnPositionsMagne = "PositionsMagne"+flnBase+".dat";
  string   hdrPositionsMagne = "#t __q[i]___ Mx My M";
  ofstream ofilePositionsMagne; 
  ofilePositionsMagne.open(flnPositionsMagne.c_str()); 
  ofilePositionsMagne << hdrPositionsMagne <<endl;
  
  
  string   flnCorrel_ij = "Correl_ij"+flnBase+".dat";
  string   hdrCorrel_ij = "#i C^m_{i,j} C^p_{i,j} DeltaTheta{i,j}";
  ofstream ofileCorrel_ij; 
  ofileCorrel_ij.open(flnCorrel_ij.c_str()); 
  ofileCorrel_ij << hdrCorrel_ij <<endl;
  
  
  string   flnCorrel_iip1 = "Correl_iip1"+flnBase+".dat";
  string   hdrCorrel_iip1 = "#i C^m_{i,i+1} C^p_{i,i+1} DeltaTheta{i,i+1}";
  ofstream ofileCorrel_iip1; 
  ofileCorrel_iip1.open(flnCorrel_iip1.c_str()); 
  ofileCorrel_iip1 << hdrCorrel_iip1 <<endl;
  
  //time p_i q_i qredu_i Ek_i Ep_i Et_i JL[i] JR[i] mx[i] my[i] Mx My
  string   flnTagParticle = "TagPartI_"+io.strTagPartI+"__"+flnBase+".dat";
  string   hdrTagParticle = "#time p_i q_i qredu_i Ek_i Ep_i Et_i JL[i] JR[i] mx[i] my[i] Mx My";
  ofstream ofileTagParticle; 
  ofileTagParticle.open(flnTagParticle.c_str()); 
  ofileTagParticle << hdrTagParticle <<endl;
  
   
  
  // Initial conditions
  ch_o.initCond(&io);
  ch_n.initCond(&io);
//  ch_o.waterBag(io.seedini, io.p0, M_PI/2.0);
//  ch_n.waterBag(io.seedini, io.p0, M_PI/2.0);
  
  //Calculate Forces.
  ch_o.calcForcesAlpha03();
  ch_n.calcForcesAlpha03();
  ch_o.calcEk_i();
  ch_o.calcEp_Alpha();
  ch_o.calcFluxAlpha02();
  ofileNrg << ch_o.strNrgTot(tt);
  // TRANSIENT DYNAMICS
  io.ttime=0;
  while (io.ttime < io.timeTransient){
    if (io.ttime%2 == 0)
      ch_o.MolecularDynamicsNoHBs(&ch_n);
    else
      ch_n.MolecularDynamicsNoHBs(&ch_o);
    io.ttime++;
  }

  // STATIONARY STATE
  io.ttime=0;
  ch_o.calcForcesAlpha03();
  while (io.ttime < io.timeSteps){
    if (io.ttime%2 == 0)
      ch_o.MolecularDynamicsNoHBs(&ch_n);
    else
      ch_n.MolecularDynamicsNoHBs(&ch_o);
    
    
    if (io.ttime % io.taux == 0 ){
      ch_o.calcEk_i();
      ch_o.calcEp_Alpha();
      ch_o.calcFluxAlpha02();
      ts.add(&ch_o);
      ts.addCorrelations(&ch_o, ch_o.N/2);
    }
    
    // Save data in files
    if (io.ttime % io.tauxSave == 0){
      if(io.printTVR) {
        //Quiero imprimir las medias temporales
        
      }
      tt=io.ttime*io.dt;
      ofileTagParticle << ch_o.strTagParticle(tt,io.tagPartI);
      //ofilePositionsMagne<<ch_o.strPositionsMagne(tt);    
      ofileNrg        << ch_o.strNrgTot(tt);
      ofileNrgMeanTmp << ts.strEnergMeanTmp(tt);
    }
    io.ttime++;
  }
  
  ofileTagParticle << ch_o.getParams();
  ofileTagParticle << io.getParams();
  ofileTagParticle.close();
  
  ofilePositionsMagne.close();
  cout<< ch_o.strPhaseSpace(tt);
  ofileNrgMeanTmp.close();

  ts.getTimeMean();
  ts.getTimeCorrel(ch_o.N/2);

  ofileTempFluxI << ts.strTempFluxI();
  ofileTempFluxI << io.getParams();
  ofileTempFluxI << ts.strEnergyMean(ch_o.alpha, ch_o.NtildeTot);
  ofileTempFluxI.close();
  
  ofileCorrel_ij << ts.strTimeCorrel_ij();
  ofileCorrel_iip1 << ts.strTimeCorrel_iip1();
  ofileCorrel_ij.close();
  ofileCorrel_iip1.close();
  
  ofileNrg << ts.strEnergyMean(ch_o.alpha, ch_o.NtildeTot);
  ofileNrg.close();
    
  string   flnEND = "MicroState"+flnBase+".end";
  ofstream ofileEND; ofileEND.open(flnEND.c_str()); 
  ofileEND << ch_o.strMicroState(tt) <<endl;
  ofileEND << "#t";
  for (int i=0; i<io.N; i++) ofileEND << " p_" << i<<" q_" << i;
  ofileEND << endl;
  ofileEND << io.getParams();
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
