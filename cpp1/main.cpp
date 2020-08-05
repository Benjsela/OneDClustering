#include<stdio.h>
#include "definitions.hpp"
#include "cluster1.hpp"
#include<vector>
#include "../DistLibrary/customDistributions.hpp"
#include "utils.hpp"
#include "../CppSimIO/fileIO.hpp"



std::vector<double> *  test1(){
  int Ni = 100;
  double p1 = .25;
  double p2 = .45;
  double p3 = .65;
  double p4 = .85;
  binomialDist * B1 = new binomialDist(p1,Ni);
  binomialDist * B2 = new binomialDist(p2,Ni);
  binomialDist * B3 = new binomialDist(p3,Ni);
  binomialDist * B4 = new binomialDist(p4,Ni);
  std::vector<DistGen_Abstract * > * v = new std::vector<DistGen_Abstract *>();
  v->push_back(B1);
  v->push_back(B2);
  v->push_back(B3);
  v->push_back(B4);
  std::vector<double> * w = new std::vector<double>();
  w->push_back(.25);
  w->push_back(.25);
  w->push_back(.25);
  w->push_back(.25);
  
  composite_Dist * D1 = new composite_Dist(0,200,w,v);
  std::vector<double> * data = new std::vector<double>();
  for(int i=0;i<200;i++){
    double a = D1->sampleF();
    printf("a = %f\n",a);
    data->push_back(a);
  }
  return data;
  // cluster1Dslow1(3,data);
}

/*
int testClusters(std::vector<double> * data, std::vector<int> * num){
  std::vector<double> * cost = new std::vector<double>();
  int s = num->size();
  for(int i=0;i<s;i++){
    oneDCluster * c = cluster1Dslow1(num->at(i),data);
    cost->push_back(c);
    //    printf("COST = %f\n",c);
  }
  int g = cost->size();
  for(int i=0;i<g;i++){
    printf("COST[%d] = %f\n",num->at(i),cost->at(i));
  }
  

}
*/


int main(){
  //std:vector<double> * data = test1();
  
  std::vector<double> * x = new std::vector<double>();
  x->push_back(4);
  x->push_back(6);
  x->push_back(10);
  x->push_back(13);
  x->push_back(20);
  x->push_back(23);
  cluster1Dslow1(3,x);
  std::vector<int> * num = new std::vector<int>();
  num->push_back(2);
  num->push_back(3);
  num->push_back(4);
  num->push_back(5);
  num->push_back(6);
  num->push_back(7);
  std::vector<double> * data = test1(); 
  // num->push_back(7);
  //testClusters(data,num);
  tryClusters(data,num);
  
}






