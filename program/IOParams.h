#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include <boost/program_options.hpp>
namespace po = boost::program_options;


#ifndef IOPARAMS_H
#define	IOPARAMS_H

using namespace std;

class IOParams{
  public:
    // input parameters
    int N;
    double U0;
    double T1;
    double T2;
    int timeSteps;
    int timeTransient;
    double eps;
    double k;
    double kp;
    double gamma1;
    double gamma2;
    int job_id;
    double alpha;
    int initCondMethod;
    double p0;
    double q0;
    double T0;
    double M0;
    
    int tagPartI;
    int partID_flux;
    int printTVR; // must be a bool type, 0 don't save
    long unsigned int seed;
    long unsigned int seed01_1;
    long unsigned int seed01_2;
    long unsigned int seed02_1;
    long unsigned int seed02_2;
    long unsigned int seedini;
    int ntrials;
    
    
    //var to name the file
    string strN;
    string strU0;
    string strT1;
    string strT2;
    string strEps;
    string strK;
    string strKp;
    string strJob_id; // job_id
    string strAlpha;  
    
    string strP0;
    string strQ0;
    string strT0;
    string strM0;
    
    string strTagPartI; //Tag particle to follow his movement

//    string prmfilename; //Default parameters file
        
    string basename;        
    string inifilename;
    
    // output variables
    string outfilename;
    string outfilename2;
    string outfilename3;
    string outfilename4;
    //string outfilename5;
    
    // auxiliar variables
    int ttime;
    int timeDim;
    int timeSave;
    int taux;
    int tauxSave;
    double dt;
    double dt2;  
    
    
    IOParams(int argc, char **argv);
    bool existInifile();
    ~IOParams();
    void printParams();
    string getParams();
    
};


#endif	/* IOPARAMS_H */
