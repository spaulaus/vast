#include <string>
#include <vector>
#include <utility>

#include "SimConvoluter.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> names = {"0069", "0113", "0152", "0209", "0298",
                            "0300", "0440", "0613", "0908", "1000",
                            "1373", "2097", "5000"};
    SimConvoluter(names, "tofs_8keVee/", make_pair(0,200));
}
