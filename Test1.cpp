#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <vector>
#include <cmath>
#include "DataTest/var.cpp"
#include "SM.cpp"
#include <limits>


using namespace std;

int main () {

  Geeks gee;

  std::vector<double> vin1 (std::begin(v1), std::end(v1));

  std::vector<double> vin2 (std::begin(v2), std::end(v2));

  std::vector<double> vin3 (std::begin(v3), std::end(v3));

  std::vector<std::vector<double> > vin;
  vin.push_back(vin1);
  vin.push_back(vin2);
  vin.push_back(vin3);

  std::vector<double> series (std::begin(y12), std::end(y12));


  gee.calculateGamma(vin, series);
  std::cout << gee.Gamma << '\n';

  std::vector<double> VAL(std::begin(uval),std::end(uval));
  std::cout << gee.SetMemebership(VAL);
  gee.readDataSet("DataTest/SetMembershipData.csv",3);
  return 0;
}
