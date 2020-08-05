#include "definitions.hpp"
#include<vector>






double oneDCluster::getCostCluster(int clusterID){
  std::vector<int> * p = this->lbIndex;
  int ind1 = int(p->at(clusterID));
  int ind2 = int(p->at(clusterID+1));
  double cost = (this->C)[ind2][ind1-1];
  return cost;
}


oneDCluster::oneDCluster(std::vector<double> * data, std::vector<int> * lbIndex, double ** C,double cost ){
  this->C = C;
  this->data = data;
  this->lbIndex = lbIndex;
  this->cost = cost;
}

