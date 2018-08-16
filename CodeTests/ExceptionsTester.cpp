//
// Created by sherksecret on 8/15/18.
//

#include <iostream>
#include <vector>
#include <complex>
#include "../File.h"

using namespace std;

int main() {
    File f("../Test/not_exist_file.bin");
    int n = 4;
    f << rw_t<int>{&n, 1};
}