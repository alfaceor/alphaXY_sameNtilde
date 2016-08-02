#include "HeatBath.h"

HeatBath::HeatBath(double mass, double gamma, double KT, double dt, double dt2, long unsigned int seed1, long unsigned int seed2 ){
  this->mass = mass;
  this->gamma = gamma;
  this->KT = KT;
  this->dt = dt;
  this->seed1 = seed1;
  this->seed2 = seed2;
  
  // XXX: There must be fluctuation and dissipation term.
  this->exist = false;
  if(  KT   > 0.0 ) this->exist =true;
  if( gamma > 0.0 ) this->exist =(this->exist and true);
  
  // Generate parameters
  this->c = new double[4];
  if( this->exist){
    double gammadt= gamma*dt;
    
    this->c[0] = exp(-gammadt);
    this->c[1] = (1.0-this->c[0])/gammadt;
    this->c[2] = (1.0-this->c[1])/gammadt;
    this->c[3] = (0.5-this->c[2])/gammadt;

    this->sigma_v2 = (KT/mass)*(1.0 - this->c[0]*this->c[0]);
    this->sigma_r2 = dt2*(KT/mass)*( 2.0-(3.0 - 4.0*this->c[0] + this->c[0]*this->c[0])/gammadt)/gammadt;

    this->sigma_v = sqrt(this->sigma_v2);
    this->sigma_r = sqrt(this->sigma_r2);
    this->corr_rv = dt*(KT/mass)*(1.0-this->c[0])*(1.0-this->c[0])/(this->sigma_r*this->sigma_v*gammadt);

    this->aux1 = this->sigma_v*this->corr_rv;
    this->aux2 = this->sigma_v*sqrt(1-this->corr_rv*this->corr_rv);

//    cout<<"#gammadt c0 c1 c2 KT sigma_v sigma_r corr_rv"<<endl;
//    cout<<"#"<<gammadt<<" "<<this->c[0]<<" "<<c[1]<<" "<<c[2]<<" "<<KT<<" "<<sigma_v<<" "<<sigma_r<<" "<<corr_rv<<endl;


    this->Trng1 = gsl_rng_default;
    this->Trng2 = gsl_rng_default;
  //  gsl_rng *r1;
    this->r1 = gsl_rng_alloc(this->Trng1);
    this->r2 = gsl_rng_alloc(this->Trng2);
  //  seed = (long unsigned int) time(NULL);
    gsl_rng_set(this->r1,this->seed1);
    gsl_rng_set(this->r2,this->seed2);
  
  }else{
    this->c[0] = 1.00;
    this->c[1] = 1.00;
    this->c[2] = 0.50;
    this->c[3] = 0.00;
    
    this->Trng1 = gsl_rng_default;
    this->Trng2 = gsl_rng_default;
    this->r1 = gsl_rng_alloc(this->Trng1);
    this->r2 = gsl_rng_alloc(this->Trng2);
    
    // To avoid any possible shit!
    this->sigma_v2 = 0.0;
    this->sigma_r2 = 0.0;

    this->sigma_v = 0.0;
    this->sigma_r = 0.0;
    this->corr_rv = 0.0;

    this->aux1 = 0.0;
    this->aux2 = 0.0;
    
//    cout<<"#No Heat Bath KT = "<<this->KT<<endl;
  }
  
  this->drG =0.0;
  this->dvG =0.0;
  
}

HeatBath::~HeatBath(){
  delete[] c;
  gsl_rng_free(this->r1);
  gsl_rng_free(this->r2);
};

void HeatBath::RollTheDice(){
  if (this->exist){
  double etha1=0.0, etha2=0.0;
    etha1 = gsl_ran_gaussian(this->r1, 1);
    etha2 = gsl_ran_gaussian(this->r2, 1);
  //  cout<<etha1<<" "<<etha2<<endl;
    this->drG = this->sigma_r*etha1;
    this->dvG = this->aux1*etha1+this->aux2*etha2;
  }else{
    this->drG = 0.00;
    this->dvG = 0.00;
  }
}

string HeatBath::getParams(){
  string strReturn;
  stringstream sstm;
  sstm << "#********* HB **************" <<endl;
  sstm << "# KT      = " << KT <<endl;
  sstm << "# gamma   = " << gamma <<endl;
  sstm << "# dt      = " << dt <<endl;
  sstm << "# c0      = " << c[0] <<endl; 
  sstm << "# c1      = " << c[1] <<endl;
  sstm << "# c2      = " << c[2] <<endl;
  sstm << "# sigma_v = " << sigma_v <<endl;
  sstm << "# sigma_r = " << sigma_r <<endl;
  sstm << "# corr_rv = " << corr_rv <<endl;
  
  strReturn = ""+sstm.str();
  return strReturn;
}
