/* 
 * File:   TimeStats.h
 * Author: alfaceor
 *
 * Created on November 22, 2015, 10:01 PM
 */

#include "Chain.h"
#include <string>
#include <sstream>

#include <limits>

typedef std::numeric_limits< double > dbl;

#ifndef TIMESTATS_H
#define	TIMESTATS_H



class TimeStats {
public:
    bool QIsCountFinish;
    int N;
    int tcount;
    double *Ek_i_mean;
    double *JL_i_mean;
    double *JR_i_mean;
    double Ek_mean;
    double Ep_mean;
    double Et_mean;
    double Et2_mean;
    double Ek2_mean;
    double Ep2_mean;
    double magne2tmp;
    double M_tmean;
    double M2_tmean;
    double JL_tmean;
    double JR_tmean;
    double JL2_tmean;
    double JR2_tmean;
    
    double *mx_tmean;
    double *my_tmean;
    double *mimj_tmean; // i =N/2
    double *mi2_tmean;
    double *mimip1_tmean;
    
    double *Correl_ij;
    double *Correl_iip1;
    
    double *vi_tmean;
    double *vi2_tmean;
    double *vivj_tmean;
    double *vivip1_tmean;
    
    double *Correl_p_ij;
    double *Correl_p_iip1;
    
    double *Delta_theta_ij;
    double *Delta_theta_iip1;
    
    double strech;
    
    TimeStats(int const N);
    TimeStats(const TimeStats& orig);
    virtual ~TimeStats();
    
    void init();
    void add(Chain* ch);
    void addCorrelations(Chain* ch, int partID);
    void getTimeMean();
    void getTimeCorrel(int partID);
    string strEnergyMean(double alpha, double NtildeTot);
    string strEnergMeanTmp(double time);
    string strTempFluxI();
    string strTimeCorrel_ij();
    string strTimeCorrel_iip1();
private:

};

#endif	/* TIMESTATS_H */

