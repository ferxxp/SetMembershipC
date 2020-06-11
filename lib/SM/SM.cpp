#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <vector>
#include <cmath>
#include <sstream>
#include <limits>
#include "SM.h"


using namespace std;

  void Geeks::addData(const std::vector<std::vector<double> > Vin,const std::vector<double> Yout){
    U=Vin;
    Y=Yout;
  }
  void Geeks::calculateGamma(void){

    for (size_t i = 0; i < Y.size(); i++) {
      double Gamma_prob=0;
      std::vector<double> Current;

      for (size_t t = 0; t < U.size(); t++) {
        Current.push_back(U[t][i]);
        //std::cout << U[t][i]<<" ";
      }
      //std::cout<<endl;
      for (size_t j = i+1; j < Y.size(); j++) {
        double Norma=0;
        for (size_t k = 0; k < U.size(); k++) {
          Norma+=std::pow(U[k][j]-Current[k],2);
          //std::cout << U[k][j]<<" ";
        }
        Gamma_prob=(std::abs(Y[i]-Y[j])-error)/std::sqrt(Norma);

        if(Gamma_prob>Gamma) Gamma=Gamma_prob;

        if(Gamma_prob>112.78) {
          std::cout<< endl << j <<" - "<< i <<" norma "<< std::sqrt(Norma) <<" dif " << std::abs(Y[i]-Y[j])<<endl;
          Norma=0;
          for (size_t k = 0; k < U.size(); k++) {
            std::cout << U[k][j]<<" "<< Current[k]<<" ";
            Norma+=std::pow(U[k][j]-Current[k],2);
            std::cout << std::pow(U[k][j]-Current[k],2)<<" = "<<Norma<<endl;
          }
          std::cout<<Gamma<<endl;
        }
      }

    }
  }
  double Geeks::SetMemebership(const std::vector<double> Vin){
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
  std::vector<std::vector<double> > Geeks::readDataSet(const std::string dir,int nVar,int quant){
    std::vector<std::vector<double> > DataSet;
    string line;
    ifstream myfile;
    myfile.open (dir);
    if (myfile.is_open())
    {
      DataSet.clear();
      for (size_t j = 0; j <= nVar; j++) {
        std::vector<double> V;
        DataSet.push_back(V);
      }
      long long int lines_read;
      while ( getline (myfile,line) && lines_read< quant)
      {
        std::istringstream ss( line );

        for (size_t j = 0; j <= nVar; j++) {
          std::string s;
          if (!getline( ss, s, ',' )) break;
          DataSet[j].push_back(std::stod(s));
        }
        lines_read++;
      }
      myfile.close();



    }
    else cout << "Unable to open file";
    std::cout << int(DataSet.size()) << '\n';
    //DataSet.erase(DataSet.begin());
    std::cout << int(DataSet.size()) << '\n';

    for(auto a: DataSet){
      // for(auto b: a){
      //  std::cout << b ;
      // }
      std::cout << a[15849] << '\n';
      std::cout << a[16034] << '\n';
      std::cout << '\n' ;
    }
    return DataSet;
  }
  void Geeks::setRegresor(std::vector<std::vector<int> > Reg){
    Regresors=Reg;

  }
  void Geeks::setRegresor(std::vector<std::vector<int> > Reg, double e){
    error=e;
    Regresors=Reg;

  }
  void Geeks::prepareData(std::vector<std::vector<double> > DataSet){
    std::cout <<'a';
    size_t size=DataSet[0].size();

    long int numberIns=0;
    for(auto b:Regresors) numberIns+=b[0];

    for (size_t i = 0; i < numberIns; i++) {
      std::vector<double> a;
      U.push_back(a);
      std::cout << int(U.size()) << '\n';
    }
    std::vector<int> sumRegresors;

    std::cout <<'a';
    for (auto Variable :Regresors)
    sumRegresors.push_back(std::accumulate(Variable.begin(), Variable.end(), 0));
    int initTimeStamp = *std::max_element(std::begin(sumRegresors), std::end(sumRegresors));

    std::cout <<'\n';
    std::cout<< initTimeStamp << '\n';
    for (size_t timestamp = initTimeStamp; timestamp <= size; timestamp++) {
      long int nVar=0, row=0;
      for (auto variable:Regresors) {
        for (size_t nV = 0; nV < variable[0]; nV++) {
          U[row].push_back(DataSet[nVar][timestamp-variable[1]-nV]);
          row++;
        }
        nVar++;
      }
      Y.push_back(DataSet[nVar-1][timestamp]);
    }
    std::cout << "/* message */" << '\n';

    for(auto a: U){
      int first100=0;
      for(auto b: a){
        std::cout << b <<", ";
        if(first100>10) break;
        first100++;
      }
      std::cout << endl <<endl;
    }

    std::cout << "OUT: ";
    int first100=0;
    for(auto a: Y){
      std::cout << a <<", ";
      if(first100>10) break;
      first100++;
    }
    std::cout << endl;
    std::cout <<U.size()<< endl;

  }
  void Geeks::prepareData(std::vector<std::vector<double> > DataSet, std::vector<std::vector<double> >& Uin, std::vector<double>& Yout){
    std::cout <<'a';
    size_t size=DataSet[0].size();

    long int numberIns=0;
    for(auto b:Regresors) numberIns+=b[0];

    for (size_t i = 0; i < numberIns; i++) {
      std::vector<double> a;
      U.push_back(a);
      std::cout << int(U.size()) << '\n';
    }
    std::vector<int> sumRegresors;

    std::cout <<'a';
    for (auto Variable :Regresors)
    sumRegresors.push_back(std::accumulate(Variable.begin(), Variable.end(), 0));
    int initTimeStamp = *std::max_element(std::begin(sumRegresors), std::end(sumRegresors));

    std::cout <<'\n';
    std::cout<< initTimeStamp << '\n';
    for (size_t timestamp = initTimeStamp; timestamp <= size; timestamp++) {
      long int nVar=0, row=0;
      for (auto variable:Regresors) {
        for (size_t nV = 0; nV < variable[0]; nV++) {
          U[row].push_back(DataSet[nVar][timestamp-variable[1]-nV]);
          row++;
        }
        nVar++;
      }
      Y.push_back(DataSet[nVar-1][timestamp]);
    }
    std::cout << "/* message */" << '\n';

    for(auto a: U){
      int first100=0;
      for(auto b: a){
        std::cout << b <<", ";
        if(first100>10) break;
        first100++;
      }
      std::cout << endl <<endl;
    }

    std::cout << "OUT: ";
    int first100=0;
    for(auto a: Y){
      std::cout << a <<", ";
      if(first100>10) break;
      first100++;
    }
    std::cout << endl;
    std::cout <<U.size()<< endl;

  }
