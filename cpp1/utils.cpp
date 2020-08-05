#include "utils.hpp"
#include "cluster1.hpp"
#include<boost/filesystem.hpp>
#include<fstream>

int tryClusters(std::vector<double> * data, std::vector<int> * num){
  std::vector<oneDCluster *> * clusters = new std::vector<oneDCluster *>();
  std::vector<double> * cost = new std::vector<double>();
  int s = num->size();
  for(int i=0;i<s;i++){
    oneDCluster * c = cluster1Dslow1(num->at(i),data);
    clusters->push_back(c);
    cost->push_back(c->cost);
    //    printf("COST = %f\n",c);
  }
  int g = cost->size();
  for(int i=0;i<g;i++){
    printf("COST[%d] = %f\n",num->at(i),(clusters->at(i))->cost);
  }
  std::vector<double> * x = new std::vector<double>();
  for(int i=0;i<s;i++){
    x->push_back(double(num->at(i)));
  }
  std::string * name = new std::string("plotA");
  std::string * dir = new std::string("plots/fig1");
  plot1dVec(x,cost,cost->size(),name,dir);

}




