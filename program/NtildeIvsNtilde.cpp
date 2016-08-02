/* 
 * File:   heatBathTest.cpp
 * Author: alfaceor
 *
 * Created on November 13, 2015, 2:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>


#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "IOParams.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  
  IOParams io(argc, argv);
//  io.printParams();
  const gsl_rng_type *T; T = gsl_rng_default;
  gsl_rng *r; r = gsl_rng_alloc(T);
  long unsigned int seed;
  seed = 0; //(long unsigned int) time(NULL); // Get the time of the system as seed
  gsl_rng_set(r,seed);
  
  ofstream ofilePQ, ofileNtildeI;
  ofilePQ.open("PQ.dat");
  string flnNtildeI = "NtildeI__N_"+io.strN+"__A_"+io.strAlpha+".dat";
  ofileNtildeI.open(flnNtildeI.c_str());

  double q=0.0, p =0.0;
  double factor=sqrt(2*io.gamma1*io.T1*io.dt);
  double gammadt = io.gamma1*io.dt;
  double c0 = exp(-gammadt);
  double c1 = (1-c0)/gammadt;
  double c2 = (1-c1)/gammadt;
//  cout <<"# gammadt=" << gammadt <<", c0="<< c0  
//       <<", c1="<<c1<<", c2="<<c2<<endl;

  ofileNtildeI <<"#i NtildeI" <<endl;
  double *NtildeI, *invIJalpha;
  NtildeI    = new double[io.N];
  invIJalpha = new double[io.N];
  double  NtildeTot=0.0;
  
  invIJalpha[0] = 0;
  for (int deltaIJ=1; deltaIJ<io.N; deltaIJ++){
    invIJalpha[deltaIJ] = pow(deltaIJ,-1.0*io.alpha);
  }
  
  for (int i=0; i<io.N; i++ ){
    NtildeI[i] = 0.0;
    for (int j=0; j<i; j++)
      NtildeI[i] += invIJalpha[abs(i-j)]; //pow(abs(i-j), -1.0*io.alpha );
    for (int j=i+1; j<io.N; j++)
      NtildeI[i] += invIJalpha[abs(i-j)];; //pow(abs(i-j), -1.0*io.alpha );
    
    NtildeTot +=NtildeI[i];
    ofileNtildeI << i << " " << NtildeI[i] <<endl;
  }
  NtildeTot=NtildeTot/io.N;
  ofileNtildeI <<"#N alpha NtildeTot invNtildeTot NtildeCircle invNtildeCircle"<<endl;
  ofileNtildeI <<"#"<<io.strN<<" "<<io.strAlpha<<" "
          << NtildeTot<<" "<< 1.0/NtildeTot << " "
          << NtildeI[io.N/2]<< " "<< 1.0/NtildeI[io.N/2] <<endl;
  cout <<io.strN<<" "<<io.strAlpha<<" "
          << NtildeTot<<" "<< 1.0/NtildeTot << " "
          << NtildeI[io.N/2]<< " "<< 1.0/NtildeI[io.N/2] <<endl;
  
//  while (io.ttime<io.timeSteps){    
//    q = q + c1*io.dt*p + c2*io.dt + drG;
//    p = c0*p + (c1-c2)*a*io.dt2 ;
//    a = F(q);
//    dvG = factor*gsl_ran_gaussian(r,1);
//    p = p + c2*a + dvG;
//    
//    ofilePQ<<io.ttime*io.dt<<" "<< p <<" "<< q <<endl;
//    io.ttime++;
//  }
  
  ofilePQ.close();
  ofileNtildeI.close();
  gsl_rng_free (r);
  return 0;
}

