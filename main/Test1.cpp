#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <vector>
#include <cmath>
#include "DataTest/var.cpp"

#include "SM.h"
#include <limits>


using namespace std;

int main () {
  std::vector<std::vector<int> > REGS;

  int v0[] = {1,0};
  std::vector<int> a (std::begin(v0),std::end(v0));
  REGS.push_back(a);
  int v1[] = {3,8};
  a=std::vector<int> (std::begin(v1),std::end(v1));
  REGS.push_back(a);
  int v2[] = {3,8};
  a=std::vector<int> (std::begin(v2),std::end(v2));
  REGS.push_back(a);
  int v3[] = {3,8};
  a=std::vector<int> (std::begin(v3),std::end(v3));
  REGS.push_back(a);
  int v4[] = {0,0};
  a=std::vector<int> (std::begin(v4),std::end(v4));
  REGS.push_back(a);
  int y1[] = {3,1};
  a=std::vector<int> (std::begin(y1),std::end(y1));
  REGS.push_back(a);

  Geeks gee;
  gee.setRegresor(REGS,0.5);
  gee.prepareData(gee.readDataSet("DataTest/SetMembershipData.csv",5,20000));
  gee.calculateGamma();
  std::cout << gee.Gamma << '\n';

  std::vector<double> VAL(std::begin(uval),std::end(uval));
  std::cout << gee.SetMemebership(VAL);

  return 0;
}
