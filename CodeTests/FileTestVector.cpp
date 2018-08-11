#include <iostream>
#include <vector>
#include <complex>
#include "../File.h"

using namespace std;

int mainFileTestVector() {
    File f("../Test/test_file.bin");
    vector<complex<float>> wdata = {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}};
    vector<complex<float>> rdata(wdata.size());

    f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    f.write(wdata);
    f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    f.read(rdata);

    for (size_t i = 0; i < rdata.size(); i++) {
        cout << rdata[i] << endl;
    }

    return 0;
}