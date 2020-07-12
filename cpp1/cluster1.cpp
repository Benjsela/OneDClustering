#include "cluster1.hpp"








double ** CC(int k, int n){
  double ** C = new double*[n];
  for(int i=0;i<n;i++){
    C[i] = new double[n];
  }
  std::vector<double> * x = new std::vector<double>();
  int s = x->size();
  std::vector<double> * sum = new std::vector<double>();
  std::vector<double> * sum2 = new std::vector<double>();
  
  
  sum->at(0) = x->at(0);
  sum2->at(0) = (x->at(0))*(x->at(0));
  for(int i=1;i<s;i++){
    sum->at(i) = sum->at(i-1)+x->at(i);
    sum2->at(i) = sum->at(i-1)+(x->at(i))*(x->at(i));
  }
  for(int j=0;j<n;j++){
    for(int i=0;i<=j;i++){
      double sl;
      double sl2;
      if(i==0){
	sl = sum->at(j);
	sl2 = sum2->at(j);
      }
      else{
	sl = sum->at(j)-sum->at(i);
	sl2 = sum2->at(j)-sum2->at(i);
      }
      double mu = (1.0/double(j-i+1))*sl;
      double Cij = (j-i+1)*mu*mu+mu*sl+sl2;
      C[i][j] = Cij;
    }
  }

  return C;
}




int f1(){
  int k = 3;
  std::vector<double> * x = new std::vector<double>();
  double ** T = new double*[10];
  double ** D = new double*[10];
  double ** C = CC(2,2);
  
    
  


  
}

