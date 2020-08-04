#include "customDistributions.hpp"
#include<stdio.h>
#include<vector>
#include<random>
#include<map>




#ifndef CUSTOMDISTS
#define CUSTOMDISTS


/*********************
 * Beta distribution *
 *********************/

double BetaGen::getMin(){
return this->min;
}

double BetaGen::getMax(){
return this->max;
}

BetaGen::BetaGen(double alpha, double beta,int min, int max){
  this->alpha = alpha;
  this->beta = beta;
  this->min = min;
  this->max = max;
  this->dist = new boost::random::beta_distribution<>(alpha,beta);
}

BetaGen::~BetaGen(){
  delete (this->dist);

}

std::string * BetaGen::to_string(){
    std::string * s = new std::string("Beta(");
    std::string * comma = new std::string(",");
    std::string * s3= new std::string(") over [");
    std::string * s6 = new std::string("]");

    char c_s1[10];
    sprintf(c_s1, "%f", alpha);
    std::string * s1 = new std::string(c_s1);

    char c_s2[10];
    sprintf(c_s2, "%f", beta);
    std::string * s2 = new std::string(c_s2);

    char c_s4[10];
    sprintf(c_s4, "%d", min);
    std::string * s4 = new std::string(c_s4);

    char c_s5[10];
    sprintf(c_s5, "%d", max);
    std::string * s5 = new std::string(c_s5);

    *s += *s1 + *comma + *s2 + *s3 + *s4 + *comma + *s5 + *s6;
    return s;
}


double BetaGen::sampleF(){
  return 0;
}


int BetaGen::sample(){
  //int r1 = 
  //int ans = quantile(dist,
  float r = (*(this->dist))(this->gen);
  printf("rr = %f\n",r);
  int r2 = int((max-min)*r+min);
  printf("r2 = %d\n",r2);
  return r2;
}


double BetaGen::discreteCDF(double x){
  // fraction ranges [0,1]
  // fraction(a) = 0
  // fraction(b) = (b-a)/(b-a) = 1
  /*double fraction = (double(x-this->min))/(double(this->max-this->min));
  double ans = boost::math::ibeta(this->alpha,this->beta,fraction);
  return ans;*/

  double fraction = x/(double(this->max-this->min+1));
  double ans = boost::math::ibeta(this->alpha,this->beta,fraction);
  return ans;
}


double BetaGen::PDF(double x){
  return boost::math::ibeta_derivative(this->alpha,this->beta,x);
  
  
}

std::pair<double *,double *> * BetaGen::plotPDF(double min, double max, int NumPoints){
  double curr = min;
  double * ans = new double[NumPoints];
  double * x = new double[NumPoints];
  double inc = (max-min)/(double(NumPoints));
  for(int i=0;i<NumPoints;i++){
    ans[i] = this->PDF(curr);
    x[i] = curr;
    curr = curr + inc;
  }
  std::pair<double *, double *> * f = new std::pair<double *, double *>(x,ans);
  return f;
}




//COMPOSITE_DIST STUFF---------------------------------------------------------

composite_Dist::composite_Dist(double min, double max, std::vector<double> * weights,std::vector<DistGen_Abstract *> * Distributions){
  this->min = min;
  this->max = max;
  this->distributions = Distributions;
  this->weights = weights;
  this->numDistributions = weights->size();  

}



int composite_Dist::sample(){
  return 0;
}

double composite_Dist::sampleF(){
  double total = 0;
  for(int i=0;i<numDistributions;i++){
    DistGen_Abstract * curr = (this->distributions->at(i));
    double weightCurr = weights->at(i);
    total = total + weightCurr*(curr->sampleF());
  }
  return total;
}


double composite_Dist::getMin(){
  return this->min;
}


double composite_Dist::getMax(){
  return this->max;
}


double composite_Dist::discreteCDF(double x){
  
  return 0;
}


double composite_Dist::PDF(double x){
  double ans = 0;
  for(int i=0;i<this->numDistributions;i++){
    DistGen_Abstract * curr = (this->distributions->at(i));
    ans = ans + (this->weights->at(i))*(curr->PDF(x));
  }
  return ans;
  
}


std::pair<double *,double *> * composite_Dist::plotPDF(double min, double max, int NumPoints){
  double * ans = new double[NumPoints];
  double * x = new double[NumPoints];
  double inc = (max-min)/(double(NumPoints));
  double curr = min;

  double frac = 0;
  for(int i=0;i<NumPoints;i++){
    frac = (double(i))/(double(NumPoints));
    printf("\r%f",frac);
    fflush(stdout);
    ans[i] = this->PDF(curr);
    x[i] = curr;
    curr = curr + inc;
  }
  std::pair<double *, double *> * f = new std::pair<double *, double *>(x,ans);
  return f;  
}



std::string * composite_Dist::to_string(){
  return NULL;
}


std::vector<std::pair<double *, double *>*> * composite_Dist::plotAllComps(double min,
								  double max, int numPoints){

  
  std::vector<std::pair<double *, double *>*> * ans = new std::vector<std::pair<double *, double *>*>();
  
  std::vector<DistGen_Abstract *> * dists = this->distributions;
  std::vector<DistGen_Abstract *>::iterator it = dists->begin();
  while(it!=dists->end()){
    DistGen_Abstract * currDist = *it;
    std::pair<double *, double*> * p = currDist->plotPDF(min,max,numPoints);
    ans->push_back(p);
    it++;
  }
  
  return ans;
}

//BINOMIAL DISTRIBUTION

binomialDist::binomialDist(double p, int N){
  this->p = p;
  this->N = N;
  this->dist = new boost::random::binomial_distribution<int>(N,p);
}

int binomialDist::sample(){

  return 0;
}

double binomialDist::sampleF(){
  double r = (*(this->dist))(this->gen);
  return int(r);
}


double binomialDist::getMin(){
  return 0;
}

double binomialDist::getMax(){
  return double(this->N);
}

double binomialDist::discreteCDF(double x){
  
  
}

std::string * binomialDist::to_string(){
  return NULL;
}

double binomialDist::PDF(double k){
  double ans = boost::math::ibeta_derivative(k+1,this->N - k+1,this->p);
  ans = ans/(double(N+1));
  return ans;
}


std::pair<double *,double *> * binomialDist::plotPDF(double min, double max, int NumPoints){
  double inc = (max-min)/(double(NumPoints));
  double curr = min;
  double * ans = new double[NumPoints];
  double * x = new double[NumPoints];
  for(int i=0;i<NumPoints;i++){
    ans[i] = this->PDF(curr);
    x[i] = curr;
    curr = curr + inc;
  }
  std::pair<double *, double *> * f = new std::pair<double *, double *>(x,ans);
  return f;

}


//NORMALDIST--------------------------------------------------------------------------
NormalDist::NormalDist(double mean, double stdev){
  this->dist = new boost::normal_distribution<>(mean,stdev);
  this->bounded = 0;
  this->mean = mean;
  this->stdev = stdev;
}


NormalDist::NormalDist(double mean, double stdev, double min, double max){
  this->bounded = 1;
  this->max = max;
  this->min = min;
  this->mean = mean;
  this->stdev = stdev;
  this->dist = new boost::normal_distribution<>(mean,stdev);
}

int NormalDist::sample(){
  double r = (*(this->dist))(this->gen);
  return int(r);  
}


double NormalDist::boundedSampleF(){
  double r = 0;
  for(int i=0;i<10;i++){
    double r = (*(this->dist))(this->gen);
    if(r<this->min){
      r = this->min;
      
    }
    else if(r>this->max){
      r = this->max;
    }
    else{
      return r;
    }
  }
  return r;

}

double NormalDist::sampleF(){
  double r = 0;
  if(this->bounded==0){
    r = (*(this->dist))(this->gen);
  }
  else{
    r = this->boundedSampleF();
  }
  return r;
}

double NormalDist::getMin(){

  
}

double NormalDist::getMax(){

  
}

double NormalDist::discreteCDF(double x){

  
}

std::string * NormalDist::to_string(){

  return NULL;
}

double NormalDist::PDF(double x){

  
}

std::pair<double *, double *>* NormalDist::plotPDF(double min, double max, int NumPoints){

  
}






/************************
 * Uniform distribution *
 ************************/

double UniformGen::getMin(){
return this->min;
}

double UniformGen::getMax(){
return this->max;
}

// integers
UniformGen::UniformGen(int min, int max){
  this->min = min;
  this->max = max;
  this->dist = new std::uniform_int_distribution<>(min,max);  
}

std::string * UniformGen::to_string(){
    std::string * s = new std::string("Uniform over [");
    std::string * comma = new std::string(",");
    std::string * s3 = new std::string("]");

    char c_s1[10];
    sprintf(c_s1, "%d", min);
    std::string * s1 = new std::string(c_s1);

    char c_s2[10];
    sprintf(c_s2, "%d", max);
    std::string * s2 = new std::string(c_s2);

    *s += *s1 + *comma + *s2 + *s3;
    return s;
}

int UniformGen::sample(){
  int v = (*(this->dist))(this->gen);
  return v;
}

double UniformGen::sampleF(){
  return 0;
}

double UniformGen::discreteCDF(double x){
  // cdf(a) = 0
  // cdf(b) = (b-a)/(b-a) = 1
  // cdf(b-1) = (b-a-1)/(b-a)
  // cdf(b)-cdf(b-1) = ((b-a)-(b-a-1))/(b-a)
  //                 = 1/(b-a)
  double ans = (double(x-this->min))/(double(this->max-this->min));
  return ans;
}



double UniformGen::PDF(double x){
  return 0;
}

std::pair<double *, double *> * UniformGen::plotPDF(double min, double max, int numPoints){
  return NULL;
}

/*
//ConstantValue
ConstantValue::ConstantValue(double value){
  this->value = value
  
}
*/


#endif
