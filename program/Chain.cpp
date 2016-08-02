/* 
 * File:   Chain.cpp
 * Author: alfaceor
 * 
 * Created on November 5, 2015, 10:12 AM
 */

#include "Chain.h"
#include "TimeStats.h"


double angleMinusPi_to_PlusPi(double angle){
  double modAngle = 0.0;
  modAngle= fmod(angle, 2*M_PI);
  if (modAngle > 0)  {
    if (modAngle <  M_PI) return modAngle;
    else return(modAngle - 2*M_PI);
  }else{
    if (modAngle > -M_PI) return modAngle;
    else return(modAngle + 2*M_PI);
  }
}

Chain::Chain(int const Np, double alpha, double k, double kp){
  this->N     = Np;
  this->alpha = alpha;
  this->p     = new double[Np];
  this->q     = new double[Np];
  this->mx    = new double[Np];
  this->my    = new double[Np];
  
  this->force = new double[Np];
//  this->fij   = new double[Np*Np];
//  this->flux   = new double[Np*Np]; // cual es el flujo de i -> j
  this->Ek_i   = new double[Np];
  this->Ep_i   = new double[Np];
  this->JL     = new double[Np];
  this->JR     = new double[Np];
  this->JLmean = 0.0;
  this->JRmean = 0.0;
  
  this->NtildeI    = new double[Np];
  this->invIJalpha = new double[Np];
  this->NtildeTot  = 0.0;
  
  this->k   = k;
  this->kpL = kp; //Make kprime equal to k by default.
  this->kpR = kp;
  
  dt=0.0;
  dt2=0.0;
  
  initPzero();
  initQzero();
  initMzero();
  initNtildeI();
  initEk_i();
  initEp_i();
  initForceZero();
  initFluxZero();
  
//  calcInvNtildeI();
//  this->k = k/NtildeTot;
}

Chain::~Chain() {
  delete[] p;
  delete[] q;
  delete[] mx;
  delete[] my;
  
  delete[] invIJalpha;
  delete[] NtildeI;
  
  delete[] Ek_i;
  delete[] Ep_i;
  
  delete[] force;
//  delete[] flux;
  delete[] JL;
  delete[] JR;
}
//
//Chain::Chain(const Chain& orig) {
//  
//}

void Chain::initPzero(){
  for (int i=0; i<N; i++){
    p[i] = 0.0;
  }
}

void Chain::initQzero(){
  for (int i=0; i<N; i++){
    q[i] = 0.0;
  }
}

void Chain::initMzero() {
  for (int i=0; i<N; i++){
    mx[i] = 0.0;
    my[i] = 0.0;
  }
}

void Chain::initNtildeI() {
  for(int i=0; i<N; i++){
    invIJalpha[i] = 0.0;
    NtildeI[i] = 0.0;
    NtildeTot  = 0.0;
  }
}

void Chain::initEk_i(){
  for (int i=0; i<N; i++){
    Ek_i[i] = 0.0;
  }
}

void Chain::initEp_i(){
  for (int i=0; i<N; i++){
    Ep_i[i] = 0.0;
  }
}

void Chain::initForceZero(){
  for (int i=0; i<N; i++){
    force[i] = 0.0;
  }
}

void Chain::initFluxZero(){
  for (int i=0; i<N; i++){
//    for (int j=0; j<N; j++){
//      flux[indx(i,j,N)] = 0.0;
//    }
    JL[i]=0.0;
    JR[i]=0.0;
  }
}


void Chain::calcInvNtildeI_divN_incorrect(){
  invIJalpha[0] = 0;
  for (int deltaIJ=1; deltaIJ<N; deltaIJ++){
    invIJalpha[deltaIJ] = pow(deltaIJ,-1.0*alpha);
  }
  for (int i=0; i<N; i++ ){
    NtildeI[i] = 0.0;
    for (int j=0; j<i; j++)
      NtildeI[i] += invIJalpha[abs(i-j)]; //pow(abs(i-j), -1.0*io.alpha );
    for (int j=i+1; j<N; j++)
      NtildeI[i] += invIJalpha[abs(i-j)];; //pow(abs(i-j), -1.0*io.alpha );
    
    NtildeTot += NtildeI[i];
  }
  NtildeTot = NtildeTot/N;
}

void Chain::calcInvNtildeI(){
  invIJalpha[0] = 0;
  for (int deltaIJ=1; deltaIJ<N; deltaIJ++){
    invIJalpha[deltaIJ] = pow(deltaIJ,-1.0*alpha);
  }
  for (int i=0; i<N; i++ ){
    NtildeI[i] = 0.0;
    for (int j=0; j<i; j++)
      NtildeI[i] += invIJalpha[abs(i-j)]; //pow(abs(i-j), -1.0*io.alpha );
    for (int j=i+1; j<N; j++)
      NtildeI[i] += invIJalpha[abs(i-j)];; //pow(abs(i-j), -1.0*io.alpha );
    
    NtildeTot += NtildeI[i];
  }
  NtildeTot = NtildeTot/(N-1.0);
}


void Chain::initCond(IOParams* io){
  double Temp = 0.0;
  switch (io->initCondMethod){
    case 0:
      cout << "Initial condition  0" <<endl;
      // All values are zero
      break;
    case 1:
      cout << "Initial condition  1" <<endl;
      // Read values from file .ini
      
      if ( initCondFromFile(io->inifilename) ){
      
      }
      else{
        cout << "Can't read the file "<< io->inifilename <<endl;
        cout << "Initial condition  2" <<endl;
        initCond_UnifP_UnifQ(io->seedini, io->p0, io->q0);
      }
      break;
    case 2:
      cout << "Initial condition  2" <<endl;
      initCond_UnifP_UnifQ(io->seedini, io->p0, io->q0);
      break;
    case 3:
      cout << "Initial condition  3" <<endl;
      Temp = 0.5*(io->T1+io->T2);
      initCond_UnifP_UnifQ(io->seedini, sqrt(1.5*Temp), 0.0);
      break;
    case 4:
      cout << "Initial condition  4" <<endl;
      Temp = 0.5*(io->T1+io->T2);
      initCond_GausP_UnifQ(io->seedini, Temp, io->q0);
      break;
    case 5:
      cout << "Initial condition  5" <<endl;
      Temp = 0.5*(io->T1+io->T2);
      initCond_GausP_UnifQ(io->seedini, Temp, 0.0);
      break;
    case 6:
      cout << "Initial condition  6" <<endl;
      cout << "io->T0 = " << io->T0 <<endl;
      cout << "io->q0 = " << io->q0 <<endl;
      initCond_GausP_UnifQ(io->seedini, io->T0, io->q0);
      break;
    case 7:
      cout << "Initial condition  7" <<endl;
      cout << "io->T0 = " << io->T0 <<endl;
      cout << "io->M0 = " << io->M0 <<endl;
      initCond_GausP_Magne(io->seedini, io->T0, io->q0, io->M0);
      break;
    default:
      cout << "NO METHOD SELECTED FOR INITIAL CONDITION!!!"<<endl;
  }
}


bool Chain::initCondFromFile(string filename){
  struct stat buffer;   
  // Check if file exist
  if (stat (filename.c_str(), &buffer) != 0){ 
//    cout<<filename+" doesn't Exist!"<<endl;
    return false;
  }else{
    ifstream iniCondFile;
    iniCondFile.open(filename.c_str()); //"xxxxxx.ini"
    string line;
    getline(iniCondFile,line);
//    cout<<line<<endl;
    stringstream linestream(line);
    string key;
    getline(linestream,key,' ');
    double time=atof(key.c_str());
    int i=0;
    while( getline(linestream,key,' ') ){
      this->p[i] = atof(key.c_str());
      getline(linestream,key,' ');
      this->q[i] = atof(key.c_str());
      i++;
    }   

    if(i>this->N or i<this->N){
      cout<<"Caralho! Deu merda! o numero de particulas nao coincide! FDP"<<endl;
    }   

    iniCondFile.close();
    return true;
  }

}


void Chain::initCond_UnifP_UnifQ(long unsigned int seed, double p0, double q0){
  cout << "q[i] uniform between [-" << q0 <<", "<<q0<<"] and "
       << "p[i] uniform between [-" << p0 <<", "<<p0<<"] for every i. ";
  cout << "Seed: " << seed <<endl;

	const gsl_rng_type *T; T = gsl_rng_default;
  gsl_rng *r; r = gsl_rng_alloc(T);
  gsl_rng_set(r,seed);

  for (int i=0; i<this->N ; i++){
    q[i] = 2.0*gsl_rng_uniform(r)*q0 - q0;
    p[i] = 2.0*gsl_rng_uniform(r)*p0 - p0;
  }
  double dP = getTotalP()/double(N);
  
  calcEk_i();
  cout<< "Ek = " <<Ek <<", Ep = " <<Ep << ", Temp =" <<"tempFactor = "<<endl;
  for (int i=0; i<N; i++){
    p[i] = p[i] - dP;
  }
  gsl_rng_free (r);
}

void Chain::initCond_GausP_UnifQ(long unsigned int seed, double Temp, double q0){
  cout << "q[i] uniform between [-" << q0 <<", "<<q0<<"] for every i and "
       << "p[i] gaussian with Temp = " << Temp << ". ";
  cout << "Seed: " << seed << endl;

	const gsl_rng_type *T; T = gsl_rng_default;
  gsl_rng *r; r = gsl_rng_alloc(T);
  gsl_rng_set(r,seed);

  double sqrtTemp = sqrt(Temp);
  for (int i=0; i<this->N ; i++){
    q[i] = 2.0*gsl_rng_uniform(r)*q0 - q0;
    p[i] = sqrtTemp*gsl_ran_gaussian(r, 1);
  }
  double dP = getTotalP()/double(N);
  cout << strPhaseSpace(0.0)<<endl;
  for (int i=0; i<N; i++){
    p[i] = p[i] - dP;
  }
  
  calcMag_i();
  calcEp_i2();
  cout << strPhaseSpace(0.0)<<endl;
  

  calcEk_i();
  double tempFactor=sqrt(N*Temp/(2.0*Ek));
  
  for (int i=0; i<N; i++){
    p[i] = p[i]*tempFactor;
  }
  calcEk_i();
  cout<< "Ek = " <<Ek <<", Ep = " <<Ep << ", Temp =" <<Temp <<"tempFactor = "<< tempFactor<<endl;
  
  gsl_rng_free (r);
}

void Chain::initCond_GausP_Magne(long unsigned int seed,double Temp, double q0, double M0){
  cout << "q[i] uniform between with a magnetization M0 ="<<M0<<"] for every i and "
       << "p[i] gaussian with Temp = " << Temp << ". ";
  cout << "Seed: " << seed << endl;

	const gsl_rng_type *T; T = gsl_rng_default;
  gsl_rng *r; r = gsl_rng_alloc(T);
  gsl_rng_set(r,seed);

  double sqrtTemp = sqrt(Temp);
  double randomValues[N];
  
  // Initiate the random values
  for (int i=0; i<this->N ; i++){
    randomValues[i] = gsl_rng_uniform(r);
  }
  
  double M02   = M0*M0;
  double M2aux = 0.0;
  for (int i=0; i<this->N ; i++){
    q[i] = 2.0*randomValues[i]*q0 - q0;
  }
  calcMag_i();
  M2aux = Mx*Mx + My*My;
  
  if (M2aux > M02){
    cout << "Magnetization founded" <<endl;
    // Reducir el angulo
  }
  
  // FIXME : UNFINISH
  calcMag_i();
  calcEp_i2();

}

void Chain::calcMag_i() {
  Mx=0.0;
  My=0.0;
  for (int i=0; i<N; i++){
    mx[i] = cos(q[i]);
    my[i] = sin(q[i]);
    Mx +=mx[i];
    My +=my[i];
  }
  Mx = Mx/N;
  My = My/N;
}


double Chain::getTotalP(){
  double totalP=0.0;
  for (int i=0; i<N; i++){
    totalP += p[i];
  }
  return totalP;
}


void Chain::waterBag(long unsigned int seed, double p0, double theta0){
  //TODO:RANDOM POSITIONS
	const gsl_rng_type *T; T = gsl_rng_default;
  gsl_rng *r; r = gsl_rng_alloc(T);
//  long unsigned int seed;
//  seed = (long unsigned int) time(NULL); // Get the time of the system as seed
  gsl_rng_set(r,seed);
//  double p0= 2.0;
  for (int i=0; i<this->N ; i++){
    //this->theta[i]=(2*gsl_rng_uniform (r)-1)*M_PI;
    q[i] = 2.0*gsl_rng_uniform (r)*theta0 - theta0;
    p[i] = gsl_rng_uniform(r)*p0 - p0/2.0;
  }
  double dP = getTotalP()/double(N);
  
  for (int i=0; i<N; i++){
    p[i] = p[i] - dP;
  }
  gsl_rng_free (r);
}



void Chain::calcEk_i(){
  Ek = 0.0;
  for (int i=0; i<N; i++){
    Ek_i[i] = 0.5*p[i]*p[i];
    Ek += Ek_i[i];
  }
}

void Chain::calcEp_i(){
  Ep = 0.0;
  for (int i=0; i<N; i++){
    Ep_i[i] = 0.0;
  }
  
  Ep_i[0]   = kpL*(1-cos(q[0]));    // Fixed BC
  Ep_i[0]  += 0.5*(k*(1-cos(q[1]-q[0])));
  Ep += Ep_i[0];
  for (int i=1; i<N-1; i++){
    Ep_i[i] = 0.5*(k*(1-cos(q[i-1]-q[i]))+k*(1-cos(q[i+1]-q[i])));
    Ep += Ep_i[i];
  }
  Ep_i[N-1]  = 0.5*(k*(1-cos(q[N-2]-q[N-1])));
  Ep_i[N-1] += kpR*(1-cos(q[N-1]));   // Fixed BC
  Ep += Ep_i[N-1];
}

// calcMag_i first
void Chain::calcEp_i2(){
  Ep = 0.0;
  for (int i=0; i<N; i++){
    Ep_i[i] = 0.0;
  }
  
  Ep_i[0]   = kpL*(1-cos(q[0]));    // Fixed BC
  Ep_i[0]  += 0.5*(k*(1- (mx[1]*mx[0] + my[1]*my[0]) ));
  Ep += Ep_i[0];
  for (int i=1; i<N-1; i++){
    Ep_i[i] = 0.5*(
              k*(1-(mx[i-1]*mx[i] + my[i-1]*my[i]))  //cos(q[i-1]-q[i])
            + k*(1-(mx[i+1]*mx[i] + my[i+1]*my[i]))  //cos(q[i+1]-q[i]
            );
    Ep += Ep_i[i];
  }
  Ep_i[N-1]  = 0.5*(k*(1- (mx[N-2]*mx[N-1] + my[N-2]*my[N-1]) ));   //cos(q[N-2]-q[N-1])
  Ep_i[N-1] += kpR*(1-cos(q[N-1]));   // Fixed BC
  Ep += Ep_i[N-1];
}


void Chain::calcEp_Alpha(){
  Ep = 0.0;
  for (int i=0; i<N; i++){
    Ep_i[i] = 0.0;
  }
  Ep_i[0]   = kpL*(1-cos(q[0]));    // Fixed BC
  for (int j=1; j<N; j++){
    Ep_i[0]  += 0.5*(k*(1- (mx[j]*mx[0] + my[j]*my[0]) ))*invIJalpha[abs(-j)];
  }
  Ep += Ep_i[0];
  for (int i=1; i<N-1; i++){
    for (int j=0; j<N; j++){
      if (j<i)
        Ep_i[i] += 0.5*k*(1-(mx[j]*mx[i] + my[j]*my[i]))*invIJalpha[abs(i-j)];
      if (j>i)
        Ep_i[i] += 0.5*k*(1-(mx[j]*mx[i] + my[j]*my[i]))*invIJalpha[abs(i-j)];
    }
    Ep += Ep_i[i];
  }
  for (int j=0; j<N-1; j++){
    Ep_i[N-1] += 0.5*(k*(1- (mx[j]*mx[N-1] + my[j]*my[N-1]) ))*invIJalpha[abs(N-1-j)];
  }
  Ep_i[N-1] += kpR*(1-cos(q[N-1]));   // Fixed BC
  Ep += Ep_i[N-1];
}


void Chain::calcFluxFNB(){
  double fij=0.0;
  JLmean=0.0;
  JRmean=0.0;
  for (int i=0; i<N; i++){
    JL[i]=0.0;
    JR[i]=0.0;
    for (int j=0; j<N; j++){
//      flux[indx(i,j,N)] = 0.0;
      if (j==i-1){
        fij = k*(sin(q[j]-q[i]));
//        flux[indx(i,j,N)] = 0.5*(p[j]+p[i])*fij;
//        JL[i] += flux[indx(i,j,N)];
        JL[i] += 0.5*(p[j]+p[i])*fij;
      }
      if (j==i+1){
        fij = k*(sin(q[j]-q[i]));
//        flux[indx(i,j,N)] = 0.5*(p[j]+p[i])*fij;
//        JR[i] += flux[indx(i,j,N)];
        JR[i] += 0.5*(p[j]+p[i])*fij;
      }
    }
    if (i>1 && i<N-2){
      JLmean += JL[i];
      JRmean += JR[i];
    }
  }
  JLmean = JLmean / (N-4);
  JRmean = JRmean / (N-4);
}

void Chain::calcFluxFNB02(){
  double fij=0.0;
  JLmean=0.0;
  JRmean=0.0;
  for (int i=0; i<N; i++){
    JL[i]=0.0;
    JR[i]=0.0;
    for (int j=0; j<N; j++){
      if (j==i-1){
        fij = k*(my[j]*mx[i]-mx[j]*my[i]);
        JL[i] += 0.5*(p[j]+p[i])*fij;
      }
      if (j==i+1){
        fij = k*(my[j]*mx[i]-mx[j]*my[i]);
        JR[i] += 0.5*(p[j]+p[i])*fij;
      }
    }
    if (i>1 && i<N-2){
      JLmean += JL[i];
      JRmean += JR[i];
    }
  }
  JLmean = JLmean / (N-4);
  JRmean = JRmean / (N-4);
}

void Chain::calcFluxAlpha(){
  double fij=0.0;
  JLmean=0.0;
  JRmean=0.0;
  for (int i=0; i<N; i++){
    JL[i]=0.0;
    JR[i]=0.0;
    for (int j=0; j<N; j++){
//      flux[indx(i,j,N)] = 0.0;
      if (j<i){
//        fij = k*(sin(q[j]-q[i]))*invIJalpha[abs(i-j)];
//        flux[indx(i,j,N)] = 0.5*(p[j]+p[i])*fij;
//        JL[i] += flux[indx(i,j,N)];
        fij = k*(my[j]*mx[i]-mx[j]*my[i])*invIJalpha[abs(i-j)];
        JL[i] += 0.5*(p[j]+p[i])*fij;
      }
      if (j>i){
//        fij = k*(sin(q[j]-q[i]))*invIJalpha[abs(i-j)];
        fij = k*(my[j]*mx[i]-mx[j]*my[i])*invIJalpha[abs(i-j)];
        JR[i] += 0.5*(p[j]+p[i])*fij;
      }
    }
    if (i>1 && i<N-2){
      JLmean += JL[i];
      JRmean += JR[i];
    }
  }
  JLmean = JLmean / (N-4);
  JRmean = JRmean / (N-4);
}

void Chain::calcFluxAlpha02(){
  double fij=0.0;
  JLmean=0.0;
  JRmean=0.0;
  for (int i=0; i<N; i++){
    JL[i]=0.0;
    JR[i]=0.0;
    for (int j=0; j<i; j++){
      fij = k*(my[j]*mx[i]-mx[j]*my[i])*invIJalpha[abs(i-j)];
      JL[i] += 0.5*(p[j]+p[i])*fij;
    }
    for (int j=i+1; j<N; j++){
      fij = k*(my[j]*mx[i]-mx[j]*my[i])*invIJalpha[abs(i-j)];
      JR[i] += 0.5*(p[j]+p[i])*fij;
    }
    if (i>1 && i<N-2){
      JLmean += JL[i];
      JRmean += JR[i];
    }
  }
  JLmean = JLmean / (N-4);
  JRmean = JRmean / (N-4);
}


// The time performance is almost unaffected.
void Chain::calcFluxAlpha03(){
  double fij=0.0;
  JLmean=0.0;
  JRmean=0.0;
  for (int i=0; i<N; i++){
    JL[i]=0.0;
    JR[i]=0.0;
    for (int j=0; j<i; j++){
      fij = k*(my[j]*mx[i]-mx[j]*my[i])*invIJalpha[abs(i-j)];
      JL[i] += 0.5*(p[j]+p[i])*fij;
    }
    if (i>1 && i<N-2){
      JLmean += JL[i];
//      JRmean += JR[i];
    }
  }
  
  JLmean = JLmean / (N-4);
  JRmean = JRmean / (N-4);
}



// FIXME: add Boundary cond
string Chain::strFij(double t){
  string strfij;
  stringstream sstm;
  sstm <<"# "<< t <<endl;
  double *fij;
  fij   = new double[N*N];

  for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
      fij[indx(i,j,N)] = 0.0;
      if (j==i+1 || j==i-1)  // delta krognecker?
        fij[indx(i,j,N)] = k*sin(q[j] - q[i]);
      sstm << fij[indx(i, j, N)] << " ";
    }
    sstm <<endl;
  }
  sstm <<endl;
  strfij = ""+ sstm.str();
  return strfij;
}

// FIXME: add Boundary cond
void Chain::calcForcesFNBdump(){
  initForceZero();
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (int i=0; i<N; i++){
//    force[i]=0.0;
    for (int j=0; j<N; j++){
      if (j==i+1 || j==i-1){
        force[i] += k*sin(q[j] - q[i]);
      }
    }
  }
  force[N-1] += kpR*sin(-q[N-1]);
}

void Chain::calcForcesFNBdump2(){
  initForceZero();
  calcMag_i();
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (int i=0; i<N; i++){
//    force[i]=0.0;
    for (int j=0; j<N; j++){
      if (j==i-1){
        force[i] += k*(my[j]*mx[i] - mx[j]*my[i]);   //sin(q[j] - q[i]);
      }
      if (j==i+1){
        force[i] += k*(my[j]*mx[i] - mx[j]*my[i]);   //sin(q[j] - q[i]);
      }
    }
  }
  force[N-1] += kpR*sin(-q[N-1]);
}

void Chain::calcForcesFNBdump3(){
//  double forzaij[6][6];
  initForceZero();
  calcMag_i();
  double fij=0.0;
  // Fixed BC
  int l = 0;
  force[l] += kpL*sin(-q[l]);
  for (int i=0; i<N-1; i++){
//    force[i]=0.0;
    l = i+1;
    fij = k*(my[i+1]*mx[i] - mx[i+1]*my[i]);    //sin(q[j] - q[i]);
//    forzaij[i][l]=  fij;
//    forzaij[l][i]= -fij;
    force[i]   +=  fij;
    force[i+1] += -fij;
  }
  l = N-1;
//  force[l] += k*(my[l+1]*mx[l] - mx[l+1]*my[l]);   //sin(q[j] - q[i]);
  force[l] += kpR*sin(-q[l]);
  
//  for (int i=0; i<N; i++){
//    for (int j=0; j<N; j++){
//      cout<< forzaij[i][j]<<"\t";
//    }
//    cout<<endl;
//  }
}


// TODO: FIXME: UNCOMPLETE
void Chain::calcForcesFNBHarmonicdump3(){
//  double forzaij[6][6];
  initForceZero();
//  calcMag_i(); //No need!
  double fij=0.0;
  // Fixed BC
  int l = 0;
  force[l] += kpL*sin(-q[l]);
  for (int i=0; i<N-1; i++){
//    force[i]=0.0;
    l = i+1;
    fij = k*(q[i+1]-q[i]);    //sin(q[j] - q[i]);
//    forzaij[i][l]=  fij;
//    forzaij[l][i]= -fij;
    force[i]   +=  fij;
    force[i+1] += -fij;
  }
  l = N-1;
//  force[l] += k*(my[l+1]*mx[l] - mx[l+1]*my[l]);   //sin(q[j] - q[i]);
  force[l] += kpR*sin(-q[l]);
  
//  for (int i=0; i<N; i++){
//    for (int j=0; j<N; j++){
//      cout<< forzaij[i][j]<<"\t";
//    }
//    cout<<endl;
//  }
}
// TODO: optimize
void Chain::calcForcesAlpha(){
  initForceZero();
  calcMag_i();
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (int i=0; i<N; i++){
//    force[i]=0.0;
    for (int j=0; j<N; j++){
      if (j<i){
        force[i] += k*(my[j]*mx[i] - mx[j]*my[i])*invIJalpha[abs(i-j)];   //sin(q[j] - q[i]);
      }
      if (j>i){
        force[i] += k*(my[j]*mx[i] - mx[j]*my[i])*invIJalpha[abs(i-j)];   //sin(q[j] - q[i]);
      }
    }
  }
  force[N-1] += kpR*sin(-q[N-1]);
}

void Chain::calcForcesAlpha02(){
  initForceZero();
  calcMag_i();
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (int i=0; i<N; i++){
    for (int j=0; j<i; j++){
      force[i] += k*(my[j]*mx[i] - mx[j]*my[i])*invIJalpha[abs(i-j)];   //sin(q[j] - q[i]);
    }
    for (int j=i+1; j<N; j++){
      force[i] += k*(my[j]*mx[i] - mx[j]*my[i])*invIJalpha[abs(i-j)];   //sin(q[j] - q[i]);
    }
  }
  force[N-1] += kpR*sin(-q[N-1]);
}


void Chain::calcForcesAlpha03(){
  initForceZero();
  calcMag_i();
  int i=0;
  int j=0;
  double fij=0.0;
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (i=0; i<N; i++){
    for (j=0; j<i; j++){
      fij = k*(my[j]*mx[i] - mx[j]*my[i])*invIJalpha[abs(i-j)];   //sin(q[j] - q[i]);
      force[i] +=  fij;
      force[j] += -fij;
    }
  }
  force[N-1] += kpR*sin(-q[N-1]);
//  
//  for (int i=0; i<N; i++){
//    for (int j=0; j<N; j++){
//      cout<< forzaij[i][j]<<"\t";
//    }
//    cout<<endl;
//  }
}


// BULLSHIT method
void Chain::calcForcesAlpha04(){
  initForceZero();
//  calcMag_i();
  double fij=0.0;
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (int i=0; i<N; i++){
    for (int j=0; j<i; j++){
      fij = k*sin(q[j] - q[i])*invIJalpha[abs(i-j)];
      force[i] +=  fij;
      force[j] += -fij;
    }
  }
  force[N-1] += kpR*sin(-q[N-1]);
}


void Chain::calcForcesAlpha05(){
  initForceZero();
  calcMag_i();
  int i=0;
  int j=0;
  double fij=0.0;
  // Fixed BC
  force[0] += kpL*sin(-q[0]);
  for (i=0; i<N; i++){
    double sum =0.0;
    for (j=0; j<i; j++){
      fij = k*(my[j]*mx[i] - mx[j]*my[i])*invIJalpha[abs(i-j)];   //sin(q[j] - q[i]);
      sum +=  fij;
      force[j] += -fij;
    }
    force[i] +=  sum;
  }
  force[N-1] += kpR*sin(-q[N-1]);
}



void Chain::calcForces(){
  double auxfij=0;
  // Fixed BC
//  force[0] += k*sin(-q[0]);
  for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
//      if (j==i+1 || j==i-1){
        auxfij= k*sin(q[j] - q[i]);
        force[i] += auxfij;
//      }else{
//        auxfij=0;
//        force[i] += auxfij; 
//      }
    }
  }
//  force[N-1] += k*sin(-q[N-1]);
}



void Chain::MolecularDynamicsHBs(Chain* n, HeatBath* hbL, HeatBath* hbR){
  hbR->RollTheDice();
  hbL->RollTheDice();
  int l;
  
  // Positons
  l=0;
  n->q[l] = q[l] 
          + hbL->c[1]*p[l]*dt + hbL->c[2]*force[l]*dt2 + hbL->drG;
  for (int i=1; i< N-1; i++)
    n->q[i] = q[i] + p[i]*dt + 0.5*force[i]*dt2;
  l=N-1;
  n->q[l] = q[l] 
          + hbR->c[1]*p[l]*dt + hbR->c[2]*force[l]*dt2 + hbR->drG;
  
  n->calcForcesAlpha05();
  
  // Momentums
  l=0;
  n->p[l] = hbL->c[0]*p[l] 
          + ((hbL->c[1]-hbL->c[2])*force[l]
            + hbL->c[2]*n->force[l])*dt + hbL->dvG;
  for (int i=1; i< N-1; i++)
    n->p[i] = p[i] + 0.5*(force[i]+n->force[i])*dt;
  l=N-1;
  n->p[l] = hbR->c[0]*p[l] 
          + ((hbR->c[1]-hbR->c[2])*force[l]
            + hbR->c[2]*n->force[l])*dt + hbR->dvG;
  
}


void Chain::MolecularDynamicsHBsFNB(Chain* n, HeatBath* hbL, HeatBath* hbR){
  hbR->RollTheDice();
  hbL->RollTheDice();
  int l;
  
  // Positons
  l=0;
  n->q[l] = q[l] 
          + hbL->c[1]*p[l]*dt + hbL->c[2]*force[l]*dt2 + hbL->drG;
  for (int i=1; i< N-1; i++)
    n->q[i] = q[i] + p[i]*dt + 0.5*force[i]*dt2;
  l=N-1;
  n->q[l] = q[l] 
          + hbR->c[1]*p[l]*dt + hbR->c[2]*force[l]*dt2 + hbR->drG;
  
  n->calcForcesFNBdump3();
  
  // Momentums
  l=0;
  n->p[l] = hbL->c[0]*p[l] 
          + ((hbL->c[1]-hbL->c[2])*force[l]
            + hbL->c[2]*n->force[l])*dt + hbL->dvG;
  for (int i=1; i< N-1; i++)
    n->p[i] = p[i] + 0.5*(force[i]+n->force[i])*dt;
  l=N-1;
  n->p[l] = hbR->c[0]*p[l] 
          + ((hbR->c[1]-hbR->c[2])*force[l]
            + hbR->c[2]*n->force[l])*dt + hbR->dvG;
  
}


void Chain::MolecularDynamicsHBsHarmonicFNB(Chain* n, HeatBath* hbL, HeatBath* hbR){
  hbR->RollTheDice();
  hbL->RollTheDice();
  int l;
  
  // Positons
  l=0;
  n->q[l] = q[l] 
          + hbL->c[1]*p[l]*dt + hbL->c[2]*force[l]*dt2 + hbL->drG;
  for (int i=1; i< N-1; i++)
    n->q[i] = q[i] + p[i]*dt + 0.5*force[i]*dt2;
  l=N-1;
  n->q[l] = q[l] 
          + hbR->c[1]*p[l]*dt + hbR->c[2]*force[l]*dt2 + hbR->drG;
  
  n->calcForcesFNBHarmonicdump3();
  
  // Momentums
  l=0;
  n->p[l] = hbL->c[0]*p[l] 
          + ((hbL->c[1]-hbL->c[2])*force[l]
            + hbL->c[2]*n->force[l])*dt + hbL->dvG;
  for (int i=1; i< N-1; i++)
    n->p[i] = p[i] + 0.5*(force[i]+n->force[i])*dt;
  l=N-1;
  n->p[l] = hbR->c[0]*p[l] 
          + ((hbR->c[1]-hbR->c[2])*force[l]
            + hbR->c[2]*n->force[l])*dt + hbR->dvG;
  
}


void Chain::MolecularDynamicsNoHBs(Chain* n){

  // Positons
  for (int i=0; i< N; i++)
    n->q[i] = q[i] + p[i]*dt + 0.5*force[i]*dt2;
  
  n->calcForcesAlpha03();
  
  // Momentums
  for (int i=0; i< N; i++)
    n->p[i] = p[i] + 0.5*(force[i]+n->force[i])*dt;
  
}

void Chain::MolecularDynamicsNoHBsFNB(Chain* n){
  
  for (int i=0; i< N; i++)
    n->q[i] = q[i] + p[i]*dt + 0.5*force[i]*dt2;
  
  n->calcForcesFNBdump3();
  
  for (int i=0; i< N; i++)
    n->p[i] = p[i] + 0.5*(force[i]+n->force[i])*dt;
  
}


string Chain::strForce(double time){
  string strforce;
  stringstream sstm;
  sstm <<"#\"time = "<< time << " \""<<endl;
  for (int i=0; i<N; i++){
      sstm << force[i] << " ";
  }
  sstm << endl;

  strforce = ""+ sstm.str();
  return strforce;
}

string Chain::getParams(){
string strReturn;
  stringstream sstm;
  sstm.precision(80);
//  sstm.flags(std::ios_base::fixed | std::ios_base::scientific);
  sstm  << "######## CHAIN PARAMS ########" << endl;
  sstm  << "# N                = " << N           <<endl;
  sstm  << "# alpha            = " << alpha       <<endl;
  sstm  << "# k (k/NtildeTot)  = " << k           <<endl;
  sstm  << "# kpL              = " << kpL         <<endl;
  sstm  << "# kpR              = " << kpR         <<endl;
  sstm  << "# NtildeTot        = " << NtildeTot   <<endl;
  sstm  << "# 2k (2k/NtildeTot)  = " << 2*k           <<endl;
  sstm  << "##############################"       << endl;
  sstm  << endl;
  strReturn =""+sstm.str();
  return strReturn;
}

string Chain::strPositionsMagne(double t){
  string parametros;
  stringstream sstm;
  
  sstm << t << " ";
  for (int i=0; i<N; i++){
    sstm <<  q[i]<< " ";
  }
  sstm << Mx << " " << My << " " << sqrt(Mx*Mx+My*My);
  sstm << endl;

  parametros = ""+ sstm.str();
  return parametros;
}


string Chain::strMicroState(double t){
  string parametros;
  stringstream sstm;
  sstm << t << " ";
  for (int i=0; i<N; i++){
    sstm << p[i] << " " << q[i]<< " ";
  }
//  sstm << endl;

  parametros = ""+ sstm.str();
  return parametros;
}

string Chain::strMag_i(double t){
  string mag_i;
  stringstream sstm;
  sstm <<"#time"<< t << " "<<endl;
  for (int i=0; i<N; i++){
    sstm << mx[i] << " " << my[i]<< endl;
  }
  sstm <<endl;
  sstm <<endl;
  mag_i = ""+ sstm.str();
  return mag_i;
}

string Chain::strPhaseSpace(double t){
  string phaseSpace;
  stringstream sstm;
  sstm <<"#\"time = "<< t << " \""<<endl;
  for (int i=0; i<N; i++){
    sstm << p[i] << " " << q[i]<<endl;
  }
  sstm << endl;
  sstm << endl;

  phaseSpace = ""+ sstm.str();
  return phaseSpace;
}

string Chain::strInvNtildeI(){
  string phaseSpace;
  stringstream sstm;
  sstm <<"# InvNtildeI for alpha="<< alpha << " \""<<endl;
  for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
    sstm << invIJalpha[abs(i-j)] << "\t ";
    }
    sstm <<endl;
  }
  sstm << endl;
  sstm << endl;

  phaseSpace = ""+ sstm.str();
  return phaseSpace;
}


string Chain::strFlux_ij(double t){
  string flux_ij;
  stringstream sstm;
  sstm <<"#\"time = "<< t << " \""<<endl;
  for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
//      sstm << flux[indx(i,j,N)] << " ";
      sstm << "OHOH ";
    }
    sstm << endl;
  }
  sstm << endl;
  sstm << endl;

  flux_ij = ""+ sstm.str();
  return flux_ij;
}


string Chain::strFlux_i(double t){
  string flux_i;
  stringstream sstm;
  sstm <<"#\"time = "<< t << " \""<<endl;
  
  double flui=0.0;
  for (int i=0; i<N; i++){
    flui = 0.0;
    for (int j=0; j<N; j++){
//      flui += flux[indx(i,j,N)];
      flui += 0;
    }
    sstm << flui <<endl;
  }

  flux_i = ""+ sstm.str();
  return flux_i;
}

string Chain::strJL(double t){
  string strReturn;
  stringstream sstm;
  sstm << t <<" "<<JLmean;
  for (int i=0; i<N; i++){
    sstm << " " <<JL[i];
  }
  sstm << endl;
  strReturn = ""+sstm.str();
  return strReturn;
}

string Chain::strJR(double t){
  string strReturn;
  stringstream sstm;
  sstm << t <<" "<<JRmean;
  for (int i=0; i<N; i++){
    sstm << " " <<JR[i];
  }
  sstm << endl;
  strReturn = ""+sstm.str();
  return strReturn;
}


string Chain::strEp_i(double t){
  string flux_ij;
  stringstream sstm;
  sstm << t << ", ";
  for (int i=0; i<N; i++){
      sstm << Ep_i[i] << ", ";
  }
  sstm << Ep << " ";
  sstm << endl;

  flux_ij = ""+ sstm.str();
  return flux_ij;
}

string Chain::strEk_i(double t){
  string strReturn;
  stringstream sstm;
  sstm << t<< " "<< Ek;
  for (int i=0; i<N; i++){
    sstm <<" "<< Ek_i[i];
  }
  sstm << endl;

  strReturn = ""+ sstm.str();
  return strReturn;
}

string Chain::strTagParticle(double t, int partID){
  double angleMean = 0.00;
  for (int i=0; i<N; i++) angleMean += angleMinusPi_to_PlusPi(q[i]);
  angleMean = angleMean/N;
  
  double qredu   = angleMinusPi_to_PlusPi(q[partID]);
  double qredup1 = angleMinusPi_to_PlusPi(q[partID+1]);
  double qredum1 = angleMinusPi_to_PlusPi(q[partID-1]);
  double qreduMeanFNB = angleMinusPi_to_PlusPi(0.5*(qredup1+qredum1));
  
  string strReturn;
  stringstream sstm;
  //time p_i q_i qredu_i <qredu> (qredu_i-<qredu>) (q_i - q_{i+1}) (q_i - (q_{i+1}+q_{i-1})/2) Ek_i Ep_i Et_i JL[i] JR[i] mx[i] my[i] Mx My
  sstm << t << " "<< p[partID] << " " << q[partID] << " "
          << qredu << " "
          << angleMean << " "
          << angleMinusPi_to_PlusPi(qredu - angleMean)    << " "
          << angleMinusPi_to_PlusPi(qredu - qredup1)      << " "
          << angleMinusPi_to_PlusPi(qredu - qreduMeanFNB) << " "
          << Ek_i[partID] << " "
          << Ep_i[partID] << " "
          << Ek_i[partID] + Ep_i[partID] << " "
          << JL[partID]   << " "
          << JR[partID]   << " "
          << mx[partID]   << " "
          << my[partID]   << " "
          << Mx << " " << My;
  sstm << endl;

  strReturn = ""+ sstm.str();
  return strReturn;
}

string Chain::strNrg_i(double t){
  string parametros;
  stringstream sstm;
  sstm <<t << " " <<endl;
  for (int i=0; i<N; i++){
    sstm << Ek_i[i] << " " << Ep_i[i]<< " "<< Ek_i[i] + Ep_i[i]<<endl;
  }
  sstm << endl;

  parametros = ""+ sstm.str();
  return parametros;
}

string Chain::strNrgTot(double t){
  string parametros;
  stringstream sstm;
  sstm.precision(17);
  sstm << t << " "<< Ek << " " << Ep << " "<< Ek+ Ep
            << " "<< JLmean<< " "<< JRmean <<endl;
  parametros = ""+ sstm.str();
  return parametros;
}




