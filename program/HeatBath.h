/**
Velocity verlet for a Langevin Dynamics

*/

#include <iostream>
#include <fstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <string>
#include <sstream>

#include <sys/stat.h>

#ifndef HEATBATH_H_
#define HEATBATH_H_

using namespace std;

class HeatBath{
  public:
    // Input parameters.
    double mass;
    double gamma;
    double KT;
    bool exist;
    double dt;
    const gsl_rng_type *Trng1, *Trng2; 
    gsl_rng *r1, *r2;
    long unsigned int seed1;
    long unsigned int seed2;
    
    // Convinient variables.
    double *c;
    double sigma_r, sigma_r2;
    double sigma_v, sigma_v2;
    double corr_rv;
    double aux1;
    double aux2;
    
    // Ouput parameters.
    double drG; // \delta r^G
    double dvG; // \delta v^G
    
    HeatBath(double mass, double gamma, double KT, double dt, double dt2, long unsigned int seed1, long unsigned int seed2 );
    ~HeatBath();
    void RollTheDice();
    string getParams();

};

#endif /* HEATBATH_H_ */
