#include<stdio.h>
#include "definitions.hpp"
#include "cluster1.hpp"
#include<vector>











int main(){
  std::vector<double> * x = new std::vector<double>();
  x->push_back(4);
  x->push_back(5);
  x->push_back(9);
  x->push_back(10);
  x->push_back(20);
  x->push_back(21);
  cluster1Dslow1(3,x);

}






