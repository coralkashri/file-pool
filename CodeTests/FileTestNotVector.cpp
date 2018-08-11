#include <iostream>
#include <vector>
#include <complex>
#include "../File.h"

using namespace std;

int mainFileTestNotVector() {
    File f("../Test/test_file.bin");

    f.init_read_write_mode(ReadWriteMode::MULTIPLE);
    for (size_t i = 0; i < 100; i++) {
        f.write(&i);
    }

    //f.close();
    //f.init_read_write_mode(ReadWriteMode::MULTIPLE);

    size_t j;
    for (size_t i = 0; i < 100; i++) {
        f.read(&j);
        cout << j << " ";
    }
    cout << endl;

    return 0;
}