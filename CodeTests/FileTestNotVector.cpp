#include <iostream>
#include <vector>
#include <complex>
#include "../src/Headers/File.hpp"

using namespace std;
using namespace FilesApi;

int mainFileTestNotVector() {
    File f("../TestFiles/test_file.bin");
    size_t elements_count = 100;

    f.init_read_write_mode(ReadWriteMode::MULTIPLE);
    for (size_t i = 0; i < elements_count; i++) {
        f.write(&i);
    }

    /*f.close();
    f.init_read_write_mode(ReadWriteMode::MULTIPLE);*/

    /// Option 1
    size_t read_single;
    for (size_t i = 0; i < elements_count / 2; i++) {
        f.read(&read_single);
        cout << read_single << " ";
    }
    cout << endl;

    /*f.close();
    f.init_read_write_mode(ReadWriteMode::MULTIPLE);*/

    /// Option 2
    size_t read_buffer[elements_count / 2];
    f.read(read_buffer, elements_count / 2);
    for (size_t i = 0; i < elements_count / 2; i++) {
        cout << read_buffer[i] << " ";
    }
    cout << endl;

    return 0;
}