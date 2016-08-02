/* 
 * File:   Chain.h
 * Author: alfaceor
 *
 * Created on November 5, 2015, 10:12 AM
 */

#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>

#include <sstream>

#include <string>

#include "HeatBath.h"
#include "IOParams.h"
#define indx(i,j,DIM) (((i)*DIM)+j)


#ifndef CHAIN_H
#define	CHAIN_H

using namespace std;

class Chain {
public:
    int N;
    double alpha;
    double k;
    double kpL, kpR;
    
    double *p;
    double *q;
    double *mx;
    double *my;
    
    // simulation paramters
    double dt;
    double dt2;
    
    double *Ek_i;
    double *Ep_i;

    double Ek;
    double Ep;
    double Mx;
    double My;
    
    double *force;
//    double *fij;
//    double *flux;
    double *JL;
    double *JR;
    double JLmean;
    double JRmean;
    
    double *invIJalpha;
    double *NtildeI;
    double NtildeTot;

    Chain(int const Np, double alpha, double k, double kp);
    void initPzero();
    void initQzero();
    void initMzero();
    void initNtildeI();
    void initEk_i();
    void initEp_i();
    void initForceZero();
    void initFluxZero();
    
    void calcInvNtildeI_divN_incorrect();
    void calcInvNtildeI();
    
    void initCond(IOParams* io);
    bool initCondFromFile(string filename);
    void initCond_UnifP_UnifQ(long unsigned int seed, double p0, double q0);
    void initCond_GausP_UnifQ(long unsigned int seed, double Temp, double q0);
    void initCond_GausP_Magne(long unsigned int seed, double Temp, double q0, double M0);
    
    void calcMag_i();
    double getTotalP();
    void waterBag(long unsigned int seed, double p0, double q0);
    void calcEk_i();
    void calcEp_i();
    void calcEp_i2(); // calcMag_i first
    void calcEp_Alpha();
    void calcFluxFNB();
    void calcFluxFNB02();
    void calcFluxAlpha();
    void calcFluxAlpha02();
    void calcFluxAlpha03();
    string strFij(double t);
    void calcForcesFNBdump();
    void calcForcesFNBdump2(); // calcMag_i first
    void calcForcesFNBdump3(); // calcMag_i first
    void calcForcesFNBHarmonicdump3();
    void calcForcesAlpha();    // calcMag_i first
    void calcForcesAlpha02();  // calcMag_i first
    void calcForcesAlpha03();  // calcMag_i first
    void calcForcesAlpha04();  // BAD METHOD
    void calcForcesAlpha05();  // calcMag_i first
    
    void calcForcesFNB();
    void calcForces();
    void MolecularDynamicsHBs(Chain* n, HeatBath* hbL, HeatBath* hbR);
    void MolecularDynamicsHBsFNB(Chain* n, HeatBath* hbL, HeatBath* hbR);
    void MolecularDynamicsHBsHarmonicFNB(Chain* n, HeatBath* hbL, HeatBath* hbR);
    
    void MolecularDynamicsNoHBs(Chain* n);
    void MolecularDynamicsNoHBsFNB(Chain* n);
    
//    string strFij(double);
    string strForce(double);
//    Chain(const Chain& orig);
    ~Chain();
    
    string getParams();
    string strPositionsMagne(double);
    string strMuState(double);
    string strMicroState(double);
    string strPhaseSpace(double);
    string strInvNtildeI();
    
    string strMag_i(double);
    string strFlux_ij(double);
    string strFlux_i(double t);
    string strJL(double t);
    string strJR(double t);
    string strEk_i(double);
    string strEp_i(double t);
    string strTagParticle(double t, int partID);
    string strNrg_i(double);
    string strNrgTot(double);
};

#endif	/* CHAIN_H */

