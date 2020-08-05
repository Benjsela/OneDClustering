#include<stdio.h>
#include<vector>





#ifndef DEFINITIONS
#define DEFINITIONS

class oneDCluster{
public:
  std::vector<double> * data;
  std::vector<int> * lbIndex;
  double ** C;
  double cost;
  double getCostCluster(int clusterID);
  oneDCluster(std::vector<double> * data, std::vector<int> * lbIndex, double ** C,double cost);



};






#endif


