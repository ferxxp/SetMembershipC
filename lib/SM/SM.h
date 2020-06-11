#ifndef SMLIB
#define SMLIB

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <vector>
#include <cmath>
#include <sstream>
#include <limits>

using namespace std;

class Geeks{
  // Access specifier
public:
  // Data Members
  double Gamma;
  std::vector<std::vector<double> > U;
  std::vector<double> Y;
  double error;
  std::vector<std::vector<int> > Regresors;

  void addData(const std::vector<std::vector<double> > Vin,const std::vector<double> Yout);
  void calculateGamma(void);
  double SetMemebership(const std::vector<double> Vin);
  std::vector<std::vector<double> > readDataSet(const std::string dir,int nVar,int quant);

  void setRegresor(std::vector<std::vector<int> > Reg);
  void setRegresor(std::vector<std::vector<int> > Reg, double e);
  void prepareData(std::vector<std::vector<double> > DataSet);
  void prepareData(std::vector<std::vector<double> > DataSet, std::vector<std::vector<double> >& Uin, std::vector<double>& Yout);
};
#endif
