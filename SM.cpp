#include <iostream>
#include <fstream>

using namespace std;
class Geeks
{
    // Access specifier
    public:

    // Data Members
    string geekname;
    double Gamma;

    // Member Functions()
    void printname()
    {
       cout << "Geekname is: " << geekname;
    }
    void calculateGamma(const std::vector<std::string> series){
      Gamma=1;
    }
    private:
        string geekname2;

};




int main () {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}
