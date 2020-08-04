#include "utils.hpp"
#include "cluster1.hpp"


int tryClusters(std::vector<double> * data, std::vector<int> * num){
  std::vector<double> * cost = new std::vector<double>();
  int s = num->size();
  for(int i=0;i<s;i++){
    double c = cluster1Dslow1(num->at(i),data);
    cost->push_back(c);
    //    printf("COST = %f\n",c);
  }
  int g = cost->size();
  for(int i=0;i<g;i++){
    printf("COST[%d] = %f\n",num->at(i),cost->at(i));
  }
  

}




