//
// Created by sherksecret on 8/15/18.
//

#include <iostream>
#include <vector>
#include <complex>
#include "../File.h"

using namespace std;

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