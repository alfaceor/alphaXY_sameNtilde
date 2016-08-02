/* 
 * File:   TimeStats.cpp
 * Author: alfaceor
 * Class to save mean, var values of the 
 * Created on November 22, 2015, 10:01 PM
 */

#include "TimeStats.h"

TimeStats::TimeStats(int const N) {
  this->N = N;
  this->tcount =0;
  this->Ek_i_mean = new double[N];
  this->JL_i_mean = new double[N];
  this->JR_i_mean = new double[N];
  
  this->mx_tmean  = new double[N];
  this->my_tmean  = new double[N];
  this->mi2_tmean = new double[N];
  
  this->mimj_tmean   = new double[N]; // i =N/2
  this->mimip1_tmean = new double[N]; // just N-1 array
  
  this->Correl_ij    = new double[N];
  this->Correl_iip1  = new double[N];
  
  this->vi_tmean     = new double[N];
  this->vi2_tmean    = new double[N];
  this->vivj_tmean   = new double[N];
  this->vivip1_tmean = new double[N];
  
  this->Correl_p_ij    = new double[N];
  this->Correl_p_iip1  = new double[N];
  
  this->Delta_theta_ij   = new double[N];
  this->Delta_theta_iip1 = new double[N];
  
  
  init();
}

void TimeStats::init(){
  for (int i=0; i<N; i++){
    Ek_i_mean[i] = 0.0;
    JL_i_mean[i] = 0.0;
    JR_i_mean[i] = 0.0;
    
    mx_tmean[i]     = 0.0;
    my_tmean[i]     = 0.0;
    mi2_tmean[i]    = 0.0;
    mimj_tmean[i]   = 0.0;
    mimip1_tmean[i] = 0.0;
    
    Correl_ij[i]   = 0.0;
    Correl_iip1[i] = 0.0;
    
    vi_tmean[i]     = 0.0;
    vi2_tmean[i]    = 0.0;
    vivj_tmean[i]   = 0.0;
    vivip1_tmean[i] = 0.0;
    
    Correl_p_ij[i]   = 0.0;
    Correl_p_iip1[i] = 0.0;
    
    Delta_theta_ij[i]   = 0.0;
    Delta_theta_iip1[i] = 0.0;
  }
  Ek_mean=0.0;
  Ep_mean=0.0;
  Ek2_mean=0.0;
  Ep2_mean=0.0;
  Et_mean =0.0;
  Et2_mean=0.0;
  JL_tmean=0.0;
  JR_tmean=0.0;
  JL2_tmean=0.0;
  JR2_tmean=0.0;
  strech = 0.0;
  
  
  tcount = 0;
  QIsCountFinish=false;
}


TimeStats::TimeStats(const TimeStats& orig) {
}

TimeStats::~TimeStats() {
  delete[] Ek_i_mean;
  delete[] JL_i_mean;
  delete[] JR_i_mean;
  delete[] mx_tmean;
  delete[] my_tmean;
  delete[] mi2_tmean;
  delete[] mimj_tmean;
  delete[] Correl_ij;
  delete[] Correl_iip1;
  delete[] Delta_theta_ij;
  delete[] Delta_theta_iip1;
}

void TimeStats::add(Chain* ch){
  if (!QIsCountFinish){
    for (int i =0; i<N; i++){
      Ek_i_mean[i] += ch->Ek_i[i];
      JL_i_mean[i] += ch->JL[i];
      JR_i_mean[i] += ch->JR[i];
    }
    Ek_mean   += ch->Ek;
    Ep_mean   += ch->Ep;

    Et_mean   += ch->Ek + ch->Ep;
    Et2_mean  += (ch->Ek + ch->Ep)*(ch->Ek + ch->Ep);

    Ek2_mean  += ch->Ek*ch->Ek;
    Ep2_mean  += ch->Ep*ch->Ep;
    JL_tmean  += ch->JLmean;
    JR_tmean  += ch->JRmean;
    JL2_tmean += ch->JLmean*ch->JLmean;
    JR2_tmean += ch->JRmean*ch->JRmean;
    
    magne2tmp  = ch->Mx*ch->Mx + ch->My*ch->My;
    M2_tmean  += magne2tmp;
    M_tmean   += sqrt(magne2tmp);
    tcount++;
  }else{
    cout<<"Can't add new values; getTimeMean method was invoked before!"<<endl;
  }
  
}


double reduceAngle(double angle){
  double modAngle = 0.0;
  modAngle= fmod(angle, 2*M_PI);
  if (modAngle < 0)  return(2*M_PI+ modAngle) ;
  else return modAngle;
}

void TimeStats::addCorrelations(Chain* ch, int partID){
  double dthiip1 = 0.0;
  for (int i=0; i< N; i++){
    mx_tmean[i]   = mx_tmean[i]   + ch->mx[i];
    my_tmean[i]   = my_tmean[i]   + ch->my[i];
    mi2_tmean[i]  = mi2_tmean[i]  + ch->mx[i]*ch->mx[i] + ch->my[i]*ch->my[i] ;
    mimj_tmean[i] = mimj_tmean[i] + ch->mx[partID]*ch->mx[i]+ch->my[partID]*ch->my[i];
    vi_tmean[i]   = vi_tmean[i]   + ch->p[i];
    vi2_tmean[i]  = vi2_tmean[i]  + ch->p[i]*ch->p[i];
    vivj_tmean[i] = vivj_tmean[i] + ch->p[partID]*ch->p[i];
    
    Delta_theta_ij[i]  = Delta_theta_ij[i]  + reduceAngle(reduceAngle(ch->q[partID])-reduceAngle(ch->q[i]));
    
    if (i != ch->N -1){
      mimip1_tmean[i] = mimip1_tmean[i] + ch->mx[i]*ch->mx[i+1]+ch->my[i]*ch->my[i+1];
      vivip1_tmean[i] = vivip1_tmean[i] + ch->p[i]*ch->p[i+1];
      dthiip1 = reduceAngle(reduceAngle(ch->q[i])-reduceAngle(ch->q[i+1]));
//      cout << ch->q[i] << " " << ch->q[i+1] << " " << dthiip1<<endl;
      strech = strech + dthiip1;
      Delta_theta_iip1[i]  = Delta_theta_iip1[i]  + dthiip1;
    }else{
      mimip1_tmean[i] = 0.0;
      vivip1_tmean[i] = 0.0;
      Delta_theta_iip1[i] = 0.0;
    }
  }
  
//  mimj_tmean[i]   = mimj_tmean[i]   + ch->mx[i]*ch->mx[j]+ch->my[i]*ch->my[j];
  

}



void TimeStats::getTimeMean(){
  if (!QIsCountFinish){
    for (int i =0; i<N; i++){
      Ek_i_mean[i] = Ek_i_mean[i]/tcount;
      JL_i_mean[i] = JL_i_mean[i]/tcount;
      JR_i_mean[i] = JR_i_mean[i]/tcount;
    }
    Ek_mean   = Ek_mean/tcount;
    Ep_mean   = Ep_mean/tcount;
    Et_mean   = Et_mean/tcount;

    Et2_mean  = Et2_mean/tcount;
    Ek2_mean  = Ek2_mean/tcount;
    Ep2_mean  = Ep2_mean/tcount;
    JL_tmean  = JL_tmean/tcount;
    JR_tmean  = JR_tmean/tcount;
    JL2_tmean = JL2_tmean/tcount;
    JR2_tmean = JR2_tmean/tcount;
    
    M2_tmean  = M2_tmean/tcount;
    M_tmean   = M_tmean/tcount;
    QIsCountFinish = true;
  }
}

void TimeStats::getTimeCorrel(int partID){
  for (int i =0; i<N; i++){
    mx_tmean[i]     = mx_tmean[i]  /tcount;
    my_tmean[i]     = my_tmean[i]  /tcount;
    mi2_tmean[i]    = mi2_tmean[i] /tcount;
    mimj_tmean[i]   = mimj_tmean[i]/tcount;
    mimip1_tmean[i] = mimip1_tmean[i] /tcount;
    
    vi_tmean[i]     = vi_tmean[i]    /tcount;
    vi2_tmean[i]    = vi2_tmean[i]   /tcount;
    vivj_tmean[i]   = vivj_tmean[i]  /tcount;
    vivip1_tmean[i] = vivip1_tmean[i]/tcount;
    
    Delta_theta_ij[i]   = Delta_theta_ij[i]  /tcount;
    Delta_theta_iip1[i] = Delta_theta_iip1[i]/tcount;
  }
  strech = strech / tcount;
  
  double sigma_m_i=0.0;
  double sigma_m_j=0.0;
  double sigma_v_i=0.0;
  double sigma_v_j=0.0;
  for (int i=0; i<N; i++){
    sigma_m_i = sqrt(mi2_tmean[partID]-(mx_tmean[partID]*mx_tmean[partID] + my_tmean[partID]*my_tmean[partID]));
    sigma_m_j = sqrt(mi2_tmean[i]-(mx_tmean[i]*mx_tmean[i] + my_tmean[i]*my_tmean[i]));
    Correl_ij[i]   = (mimj_tmean[i] - (mx_tmean[partID]*mx_tmean[i] + my_tmean[partID]*my_tmean[i]))/(sigma_m_i*sigma_m_j);
    
    sigma_v_i = sqrt(vi2_tmean[partID]- vi_tmean[partID]*vi_tmean[partID]);
    sigma_v_j = sqrt(vi2_tmean[i]- vi_tmean[i]*vi_tmean[i]);
    
    Correl_p_ij[i] = (vivj_tmean[i]-vi_tmean[partID]*vi_tmean[i])/(sigma_v_i*sigma_v_j);
    
    if (i != N -1){
      sigma_m_i = sqrt(mi2_tmean[i+1]-(mx_tmean[i+1]*mx_tmean[i+1] + my_tmean[i+1]*my_tmean[i+1]));
      Correl_iip1[i]   = (mimip1_tmean[i] - (mx_tmean[i]*mx_tmean[i+1] + my_tmean[i]*my_tmean[i+1]))/(sigma_m_i*sigma_m_j);
      
      sigma_v_i = sqrt(vi2_tmean[i+1]-vi_tmean[i]*vi_tmean[i+1]);
      Correl_p_iip1[i] = (vivj_tmean[i]-vi_tmean[i]*vi_tmean[i+1])/(sigma_v_i*sigma_v_j);;
    }else{
      Correl_iip1[i]   = 0.0;
      Correl_p_iip1[i] = 0.0;
    }
  }
  

}

string TimeStats::strTimeCorrel_ij(){
  string strReturn;
  stringstream sstm;
//  sstm.precision(17);
  for (int i=0; i<N ; i++){
    sstm  << i << " " <<  Correl_ij[i] << " " <<Correl_p_ij[i] << " " << Delta_theta_ij[i] <<endl;
  }
  strReturn =""+sstm.str();
  return strReturn;
}

string TimeStats::strTimeCorrel_iip1(){
  string strReturn;
  stringstream sstm;
//  sstm.precision(17);
  for (int i=0; i<N ; i++){
    sstm  << i << " " <<  Correl_iip1[i] << " " << Correl_p_iip1[i] << " " << Delta_theta_iip1[i] << " " << strech  <<endl;
  }
//  sstm << "# N <Correl_m_iip1> <Correl_p_iip1> mean position" <<endl;
  strReturn =""+sstm.str();
  return strReturn;
}




string TimeStats::strEnergyMean(double alpha, double NtildeTot){
  if (!QIsCountFinish){
    getTimeMean();
  }
  string strReturn;
  stringstream sstm;
//  dbl::max_digits10
//  sstm.precision(dbl::max_digits10);
  sstm.precision(17);
  sstm  << "######## Energy time statistics ########" << endl;
  sstm  << "# Ek_mean    = " << Ek_mean   <<endl;                                                                                                     
  sstm  << "# Ep_mean    = " << Ep_mean   <<endl;
  sstm  << "# Et_mean    = " << Et_mean   <<endl;
  sstm  << "# Et2_mean   = " << Et2_mean  <<endl;
  sstm  << "# Ek2_mean   = " << Ek2_mean  <<endl;
  sstm  << "# Ep2_mean   = " << Ep2_mean  <<endl;
  sstm  << "# JL_tmean   = " << JL_tmean  <<endl;
  sstm  << "# JR_tmean   = " << JR_tmean  <<endl;
  sstm  << "# JL2_tmean  = " << JL2_tmean <<endl;
  sstm  << "# JR2_tmean  = " << JR2_tmean <<endl;
  sstm  << "# JR2_tmean  = " << JR2_tmean <<endl;
  sstm  << "# M_tmean    = " << M_tmean   <<endl;
  sstm  << "# M2_tmean   = " << M2_tmean  <<endl;
  sstm  << "# DeltaEt^2  = " << Et2_mean - Et_mean*Et_mean <<endl;
  sstm  << "# DeltaEt/Et = " << sqrt(Et2_mean  - Et_mean*Et_mean  )/Et_mean  <<endl;
  sstm  << "# DeltaJL/JL = " << sqrt(JL2_tmean - JL_tmean*JL_tmean)/JL_tmean <<endl;
  sstm  << "# DeltaJR/JR = " << sqrt(JR2_tmean - JR_tmean*JR_tmean)/JR_tmean <<endl;
  sstm  << "#************************************************"<<endl;
  sstm  << "#N alpha NtildeTot EK_mean/N Ep_mean/N Et_mean/N JL_tmean M_tmean"<<endl;
  sstm  << "#"<<N<<" "<<alpha<<" "<<NtildeTot<<" "<<Ek_mean/N<<" "<<Ep_mean/N
              <<" "<<Et_mean/N<<" "<<JL_tmean<<" "<<M_tmean <<endl;
  sstm  << "########################################" << endl;
  sstm  << endl;

  strReturn =""+sstm.str();
  return strReturn;
}



string TimeStats::strEnergMeanTmp(double time){
  string strReturn;
  stringstream sstm;
  sstm.precision(17);
  sstm  << time << " " << tcount << " "
        << Et_mean  /tcount << " "  
        << Et2_mean /tcount << " "  
        << Ek_mean  /tcount << " "  
        << Ek2_mean /tcount << " "  
        << Ep_mean  /tcount << " "  
        << Ep2_mean /tcount << " "  
        << JL_tmean /tcount << " "  
        << JL2_tmean/tcount << " "  
        << JR_tmean /tcount << " "  
        << JR2_tmean/tcount << " " 
        << M_tmean  /tcount << " " 
        << M2_tmean /tcount << endl;

  strReturn =""+sstm.str();
  return strReturn;
}


string TimeStats::strTempFluxI(){
  string strReturn;
  stringstream sstm;
  sstm << "#i T_i JL_i JR_i" <<endl;
  for (int i=0; i<N; i++){
    sstm << i << " ";
    sstm << 2*Ek_i_mean[i] << " ";
    sstm << JL_i_mean[i] << " ";
    sstm << JR_i_mean[i] << " ";
    sstm << endl;
  }
  strReturn =""+sstm.str();
  return strReturn;
}

