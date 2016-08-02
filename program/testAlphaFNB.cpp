#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "IOParams.h"
#include "Chain.h"
#include "HeatBath.h"
#include "TimeStats.h"

#define indx(i,j,DIM) (((i)*DIM)+j)


using namespace std;


int main(int argc, char **argv){
  // Initiate objects.
  IOParams io(argc, argv);
  double tt=io.ttime*io.dt;
  
  Chain ch_o(io.N, io.alpha, io.k, io.kp);
        ch_o.dt= io.dt; ch_o.dt2= io.dt2;
  
  ch_o.kpL=io.kp; ch_o.kpR=io.kp;
  
  
  ch_o.initCond(&io);
  cout<<ch_o.strPhaseSpace(tt);
  
  
  // FNB
  ch_o.calcForcesFNBdump3();
  cout<<"#k = "<< ch_o.k<<endl;
  cout<<"calcForcesFNBdump ="<<ch_o.strForce(tt);
  ch_o.calcFluxFNB02();
  cout<<"calcFluxFNB "<<ch_o.strJL(tt);
  
  // ALPHA
  ch_o.initForceZero();
  cout<<"alpha="<<ch_o.alpha<<endl;
  ch_o.calcInvNtildeI();
  cout<<ch_o.strInvNtildeI();
  ch_o.k = 2.0*ch_o.k;
  cout<<"#k = "<< ch_o.k<<endl;
  ch_o.k = ch_o.k/ch_o.NtildeTot;
  cout<<"#NtildeTot = "<<ch_o.NtildeTot<<endl;
  cout<<"#k/NtildeTot = "<< ch_o.k<<endl;
  ch_o.calcForcesAlpha03();
  cout<<"#k = "<< ch_o.k<<endl;
  cout<<"calcForcesAlpha"<<ch_o.strForce(tt);
  ch_o.calcFluxAlpha03();
  cout<<"calcFluxAlpha = "<< ch_o.strJL(tt);
  
  
  
  io.strAlpha="INFT";
  // Files to save data.
  string   flnBase="__N_"+io.strN+"__A_"+io.strAlpha+"__j_"+io.strJob_id;
  

}
