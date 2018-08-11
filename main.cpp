#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include "File.h"

using namespace std;

int main() {
    File f("/home/sherksecret/Projects/CLionProjects/filesApi/Test/test_file.bin");

    bool vectors_case = false;

    if (vectors_case) {
        f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
        vector<complex<float>> wdata = {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}};
        vector<complex<float>> rdata(wdata.size());

        f.write(wdata);
        f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
        f.read(rdata);

        for (size_t i = 0; i < rdata.size(); i++) {
            cout << rdata[i] << endl;
        }

    } else {
        f.init_read_write_mode(ReadWriteMode::MULTIPLE);
        for (size_t i = 0; i < 100; i++) {
            f.write(i);
        }

        //f.init_read_write_mode(ReadWriteMode::MULTIPLE);

        size_t j;
        for (size_t i = 0; i < 100; i++) {
            f.read(j);
            cout << j << " ";
        }
        cout << endl;
    }


    return 0;
}