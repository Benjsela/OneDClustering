#include "fileIO.hpp"
#include<stdio.h>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iostream>
#include<boost/filesystem.hpp>



int testDIR(std::string * dir){
  boost::filesystem::path dstFolder = dir->c_str();
  if(!(boost::filesystem::exists(dstFolder))){
    printf("created again\n");
    boost::filesystem::create_directory(dstFolder); 
  }
}



int plot1d(double * x, double * y, int N, std::string * name, std::string * dir){
  int size = 40*N;
  char * arr = new char[size];
  int index = 0;
  int digits = 8;
  for(int i=0;i<N;i++){
    sprintf(arr+index,"%lf",x[i]);
    index+=digits;
    sprintf(arr+index,",%lf",y[i]);
    arr[index+digits+1]='\n';
    index+=digits +2;
  }
  arr[index]='\0';
  testDIR(dir);
  std::string * a = new std::string(arr);
  std::string * slash = new std::string("/");
  std::string * b = new std::string("");
  *b = *dir + *slash;
  *b = *b + *name;
  //std::string name1("./plots1/");
  printf("name is %s\n",b->c_str());
  //name1 = name1 + *name;
  FILE * file = fopen(b->c_str(),"w");
  int results = fputs(arr,file);
  fclose(file);
  delete [] arr;
}

int plot1dVec(std::vector<double> * x, std::vector<double> * y,
	      int N, std::string * name, std::string * dir){
  int size = 40*N;
  char * arr = new char[size];
  int index = 0;
  int digits = 8;
  for(int i=0;i<N;i++){
    sprintf(arr+index,"%lf",x->at(i));
    index+=digits;
    sprintf(arr+index,",%lf",y->at(i));
    arr[index+digits+1]='\n';
    index+=digits +2;
  }
  arr[index]='\0';
  testDIR(dir);
  std::string * a = new std::string(arr);
  std::string * slash = new std::string("/");
  std::string * b = new std::string("");
  *b = *dir + *slash;
  *b = *b + *name;
  //std::string name1("./plots1/");
  printf("name is %s\n",b->c_str());
  //name1 = name1 + *name;
  FILE * file = fopen(b->c_str(),"w");
  int results = fputs(arr,file);
  fclose(file);
  delete [] arr;
}




