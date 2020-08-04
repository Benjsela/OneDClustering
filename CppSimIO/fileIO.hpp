#include <stdio.h>
#include <string>
#include<vector>
int testDIR(std::string * dir);
int plot1d(double * x, double * y, int N, std::string * name, std::string * dir);
int plot1dVec(std::vector<double> * x, std::vector<double> * y,
	      int N, std::string * name, std::string * dir);
