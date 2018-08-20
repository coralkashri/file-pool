#include <iostream>
#include <vector>
#include <complex>
#include "../src/headers/FilesManager.hpp"

using namespace std;
using namespace FilesApi;

int mainFilesManagerTest() {
    FilesManager fm;
    fm.add("1", "../TestFiles/test_file.bin");
    fm.add("2", "../TestFiles/test_file2.bin");
    vector<complex<float>> wdata = {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}};
    vector<complex<float>> rdata(wdata.size());

    fm.get("1").init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    //fm.get("1").write(wdata.data(), wdata.size()); // Use it as complex<float> array. Possible.
    fm.get("1").write(wdata);
    fm.get("1").init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    fm.get("1").read(rdata);

    for (size_t i = 0; i < rdata.size(); i++) {
        cout << rdata[i] << endl;
    }


    fm.get("2").init_read_write_mode(ReadWriteMode::MULTIPLE);
    for (size_t i = 0; i < 100; i++) {
        fm.get("2").write(&i);
    }

    //f.init_read_write_mode(ReadWriteMode::MULTIPLE);

    size_t j;
    for (size_t i = 0; i < 100; i++) {
        fm.get("2").read(&j);
        cout << j << " ";
    }
    cout << endl;

    return 0;
}