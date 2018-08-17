#include <iostream>
#include <vector>
#include <complex>
#include "../src/Headers/File.hpp"

using namespace std;
using namespace FilesApi;

int mainFileTestOpertorsNotVectors() {
    File f("../TestFiles/test_file.bin");
    const size_t size = 10;
    int wdata = 0;
    int rdata[size];
    //f.init_read_flags(); // Not necessary to write
    //f.init_write_flags(); // Not necessary to write

    f.init_read_write_mode(ReadWriteMode::MULTIPLE);
    for (size_t i = 0; i < size; i++) {
        f << rw_t<int>(&wdata, 1);
        wdata += 10;
    }

    f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    f >> rw_t<int>(rdata, size);
    f.close();

    for (size_t i = 0; i < size; i++) {
        cout << rdata[i] << endl;
    }

    return 0;
}