#include <iostream>
#include <vector>
#include <complex>
#include "../src/File.hpp"

using namespace std;
using namespace FilesApi;

int mainComplexDataStructureTest() {
    File f("../TestFiles/test_file.bin");
    vector<vector<complex<float>>> wdata = {
            {{1, 9}, {3,   5},  {4,   2.4}, {1.1, 1.5}},
            {{1, 2}, {3,   4},  {5,   6},   {7,   8.16}},
            {{1, 9}},
            {{9, 8}, {2.3, 1},  {1,   2}},
            {{1, 9}, {15,  15}},
            {{1, 9}, {3,   75}, {9,   2.4}, {1.1, 15.5}},
            {{1, 9}, {1,  5.2}},
            {{1, 2}, {3,   4},  {5,   6},   {7,   8.6}}
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
            cout << rdata[i][k] << "\t\t";
        }
        cout << endl;
    }
}