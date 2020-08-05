#include "cluster1.hpp"
#include<vector>
#include<algorithm>
#include "definitions.hpp"

//some utilities for debugging--------------
int printVec(std::vector<double> * v){
  int n = v->size();
  for(int i=0;i<n;i++){
    printf("v[%d] = %f\n",i,v->at(i));
  }
}


int printMatrix(double ** M, int n1, int n2){
  for(int i=0;i<n1;i++){
    for(int j=0;j<n2;j++){
      printf("%f, ",M[i][j]);
    }
    printf("\n");
  }
  return 0;
}


//cost function for minimizing sum of within cluster distances from median
double ** CC1(int k, int n,std::vector<double> * x){
  double ** C = new double*[n];
  for(int i=0;i<n;i++){
    C[i] = new double[n];
  }
 
  int s = x->size();
  std::vector<double> * sum = new std::vector<double>();
  std::vector<double> * sum2 = new std::vector<double>();
  
  
  sum->push_back(x->at(0));
  sum2->push_back((x->at(0))*(x->at(0)));
  for(int i=1;i<s;i++){
    sum->push_back(sum->at(i-1)+x->at(i));
    sum2->push_back(sum2->at(i-1)+(x->at(i))*(x->at(i)));
  }
  for(int j=0;j<n;j++){
    for(int i=0;i<=j;i++){
      printf("(i,j) = %d,%d\n",i,j);
      double sl;
      double sl2;
      if(i==0){
	sl = sum->at(j);
	sl2 = sum2->at(j);
      }
      else{
	sl = sum->at(j)-sum->at(i-1);
	sl2 = sum2->at(j)-sum2->at(i-1);
      }
      printf("sl2 = %f\n",sl2);	
      printf("sl = %f\n",sl);
      //mu should be median element
      double mu = (1.0/(double(j-i+1)))*sl;
      double Cij = (j-i+1)*mu*mu-2*mu*sl+sl2;
      C[i][j] = Cij;
    }
  }

  return C;

}







//cost function for minimizing sum of within cluster squared distances
double ** CC(int k, int n,std::vector<double> * x){
  double ** C = new double*[n];
  for(int i=0;i<n;i++){
    C[i] = new double[n];
  }
 
  int s = x->size();
  std::vector<double> * sum = new std::vector<double>();
  std::vector<double> * sum2 = new std::vector<double>();
  
  
  sum->push_back(x->at(0));
  sum2->push_back((x->at(0))*(x->at(0)));
  for(int i=1;i<s;i++){
    sum->push_back(sum->at(i-1)+x->at(i));
    sum2->push_back(sum2->at(i-1)+(x->at(i))*(x->at(i)));
  }
  for(int j=0;j<n;j++){
    for(int i=0;i<=j;i++){
      printf("(i,j) = %d,%d\n",i,j);
      double sl;
      double sl2;
      if(i==0){
	sl = sum->at(j);
	sl2 = sum2->at(j);
      }
      else{
	sl = sum->at(j)-sum->at(i-1);
	sl2 = sum2->at(j)-sum2->at(i-1);
      }
      printf("sl2 = %f\n",sl2);	
      printf("sl = %f\n",sl);
      double mu = (1.0/(double(j-i+1)))*sl;
      double Cij = (j-i+1)*mu*mu-2*mu*sl+sl2;
      C[i][j] = Cij;
    }
  }

  return C;
}


std::vector<int> *  computeClustering(int k, double ** T, std::vector<double> * x){
  int n = x->size();
  int num = n-1;
  std::vector<double> * p = new std::vector<double>();
  std::vector<int> * index = new std::vector<int>();
  p->push_back(x->at(num));
  index->push_back(num+1);
  for(int i=0;i<k;i++){   
    double ind = T[k-i-1][num];
    printf("ind = %f\n",ind);
    num = ind-1;
    double x_ind = x->at(ind);
    index->push_back(ind);
    p->push_back(x_ind);
  }
  printVec(p);
  return index;
}


oneDCluster *  cluster1Dslow(int k, std::vector<double> * x,double ** C){
  int n = x->size();
  //std::vector<double> * x = new std::vector<double>();
  double ** T = new double*[n];
  double ** D = new double*[n];

 
  //initialize matrices
  for(int i=0;i<n;i++){
    T[i] = new double[n];
    D[i] = new double[n];
  }

  
  double a1 = C[0][1];
  printf("a1 = %f\n",a1);
  for(int m=0;m<n;m++){
    D[0][m] = C[0][m];
  }
  
  double DCurr;
  double Dmin;
  for(int i=1;i<k;i++){//num clusters
    for(int m=1;m<n;m++){//num elements to cluster
      DCurr = D[i-1][0] + C[1][m];
      D[i][m] = DCurr;
      T[i][m] = 1;
      //ARGMIN----
      for(int j=1;j<=m;j++){//j is first index for right most cluster
	DCurr = D[i-1][j-1] + C[j][m];
	if(DCurr<(D[i][m])){
	  D[i][m] = DCurr;
	  printf("DCurr = %f, j = %d\n",DCurr,j);
	  T[i][m] = j;
	}	
      }   
    }
  }
  printf("T = \n");
  printMatrix(T, n, n);
  printf("D=\n");
  printMatrix(D, n, n);  
  std::vector<int> *  p = computeClustering(k, T, x);
  double cost = 0;
  for(int i=0;i<k;i++){
    int ind1 = int(p->at(i));
    int ind2 = int(p->at(i+1));
    printf("ind1 = %d, ind2 = %d\n",ind1,ind2);
    double c1 = C[ind2][ind1-1];
    cost = cost + c1;
    printf("cost = %f\n",c1);
  }
  oneDCluster * clusterAns = new oneDCluster(x,p,C,cost);
  
  return clusterAns;;
}




oneDCluster * cluster1Dslow1(int k, std::vector<double> * x){
  std::sort (x->begin(),x->end());
  printVec(x);
  int n = x->size();
  double ** C = CC(n,n,x);
  oneDCluster *  ans = cluster1Dslow(k,x,C);

  return ans;

}



