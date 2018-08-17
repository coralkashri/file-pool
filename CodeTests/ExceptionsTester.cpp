#include <iostream>
#include <vector>
#include <complex>
#include "../File.h"

using namespace std;
using namespace FilesApi;

int mainExceptionsTest() {
    File f("../Test/not_exist_file.bin", true);
    int n = 4;
    string err;
    try {
        f << rw_t<int>{&n, 1};
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}
