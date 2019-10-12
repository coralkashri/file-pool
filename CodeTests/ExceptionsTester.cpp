#include <iostream>
#include <vector>
#include <complex>
#include "../src/File.hpp"

using namespace std;
using namespace FilesApi;

int mainExceptionsTest() {
    File f("../TestFiles/not_exist_file.bin", true);
    int n = 4;
    string err;
    try {
        f << rw_soft(n);
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}
