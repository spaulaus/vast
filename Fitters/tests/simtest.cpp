#include <string>
#include <vector>
#include <utility>

#include "ConfigurationReader.hpp"
#include "SimConvoluter.hpp"

using namespace std;

///This is used to test that the SimConvoluter is working as expected
int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "You must provide the name of the configuration file!!"
             << endl;
        cerr << "Usage: ./vast /path/to/configuration/file" << endl;
        exit(0);
    }
    SimConvoluter sim(argv[1]);
}
