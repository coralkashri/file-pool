#include <iostream>
#include <vector>
#include <complex>
#include "../File.h"

using namespace std;

int mainComplexDataStructureTest() {
    File f("../Test/test_file.bin");
    vector<vector<complex<float>>> wdata = {
            {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
            {{1, 2}, {3, 4},  {5,      6},    {7,     8.156}},
            {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
            {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
            {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
            {{1, 9}, {3, 75}, {9999,   21.4}, {153.1, 15.85}},
            {{1, 2}, {3, 4},  {5,      6},    {7,     8.156}}
    };
    vector<vector<complex<float>>> rdata(wdata.size());
    for (size_t i = 0; i < wdata.size(); i++) {
        rdata[i] = vector<complex<float>>(wdata[i].size());
    }

    //f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE); // not necessary
    f.write(wdata);
    //f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE); // not necessary
    f.read(rdata);

    for (size_t i = 0; i < rdata.size(); i++) {
        for (size_t k = 0; k < rdata[i].size(); k++) {
            cout << rdata[i][k] << endl;
        }
    }
}