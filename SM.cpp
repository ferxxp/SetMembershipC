#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <vector>
#include <cmath>
#include "DataTest/var.cpp"
#include <limits>


using namespace std;


class Geeks
{
  // Access specifier
public:

  // Data Members
  string geekname;
  double Gamma;
  std::vector<std::vector<double> > U;
  std::vector<double> Y;

  // Member Functions()
  void calculateGamma(const std::vector<std::vector<double> > Vin,const std::vector<double> Yout){
    U=Vin;
    Y=Yout;

    for (size_t i = 0; i < Yout.size(); i++) {
      double error=0.05;
      double Gamma_prob=0;
      std::vector<double> Current;
      //std::cout<<endl;
      for (size_t t = 0; t < Vin.size(); t++) {
        Current.push_back(Vin[t][i]);
        //std::cout << Vin[t][i]<<" ";
      }
      //std::cout<<endl;
      for (size_t j = i+1; j < Yout.size(); j++) {
        double Norma=0;
        for (size_t k = 0; k < Vin.size(); k++) {
          Norma+=std::pow(Vin[k][j]-Current[k],2);
          //std::cout << Vin[k][j]<<" ";
        }
        Gamma_prob=(std::abs(Yout[i]-Yout[j])-error)/std::sqrt(Norma);

        if(Gamma_prob>Gamma) Gamma=Gamma_prob;
        // if(Gamma_prob>1.7) {
        //   std::cout<< endl << j <<"-"<< i <<"norma"<< std::sqrt(Norma) <<"dif" << std::abs(Yout[i]-Yout[j])<<endl;
        //   Norma=0;
        //   for (size_t k = 0; k < Vin.size(); k++) {
        //     std::cout << Vin[k][j]<<" "<< Current[k]<<" ";
        //     Norma+=std::pow(Vin[k][j]-Current[k],2);
        //     std::cout << std::pow(Vin[k][j]-Current[k],2)<<" = "<<Norma<<endl;
        //   }
          //std::cout<<Gamma<<endl;
        //}
      }

    }
  }
  double SetMemebership(const std::vector<double> Vin){
    double Yupper=std::numeric_limits<double>::max(),Ylower=0;
    double Yupc=0,Yloc=0;
    for (size_t j = 0; j < Y.size(); j++) {
      double Norma=0;
      for (size_t k = 0; k < U.size(); k++) {
        Norma+=std::pow(Vin[k]-U[k][j],2);
      }
      Yupc=Y[j]+Gamma*std::sqrt(Norma);
      if(Yupper>Yupc) Yupper=Yupc;
      Yloc=Y[j]-Gamma*std::sqrt(Norma);
      if(Ylower<Yloc) Ylower=Yloc;
    }
    return (Yupper+Ylower)/2;
  }

};




int main () {

  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();

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
  return 0;
}
