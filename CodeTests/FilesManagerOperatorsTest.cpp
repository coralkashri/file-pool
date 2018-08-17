#include <iostream>
#include <vector>
#include <complex>
#include "../src/Headers/FilesManager.hpp"

using namespace std;
using namespace FilesApi;

int mainFilesManagerOperatorsTest() {
    FilesManager fm(false, 0, "../TestFiles/");
    string files[] = {"test_file.bin", "test_file2.bin"};

    fm["1"] = files[0];

    vector<complex<float>> wdata = {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}};
    vector<complex<float>> rdata(wdata.size());

    fm["1"].init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    //fm.get("1").write(wdata.data(), wdata.size()); // Use it as complex<float> array. Possible.
    fm["1"].write(wdata);
    fm["1"].init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    fm["1"].read(rdata);

    fm += add_data("5", files[1]); // Add file to collection
    int a = 12;
    int b;
    fm["5"] << rw_t<int>(&a, 1); // Work
    fm["5"].write(&a); // Work
    fm["5"] >> rw_t<int>(&b, 1); // Work
    cout << b << endl; // Prints 12

    fm -= "5"; // Remove the file from collection
    fm["5"] << rw_t<int>(&a, 1); // Error
    fm["5"].write(&a); // Error
    fm["5"] >> rw_t<int>(&b, 1); // Error

    //fm["2"] = files[1];
    fm += add_data("2", files[1]);

    for (size_t i = 0; i < rdata.size(); i++) {
        cout << rdata[i] << endl;
    }


    fm["2"].init_read_write_mode(ReadWriteMode::MULTIPLE);
    for (size_t i = 0; i < 100; i++) {
        fm["2"].write(&i);
    }

    //f.init_read_write_mode(ReadWriteMode::MULTIPLE);

    size_t j;
    for (size_t i = 0; i < 100; i++) {
        fm["2"].read(&j);
        cout << j << " ";
    }
    cout << endl;

    return 0;
}