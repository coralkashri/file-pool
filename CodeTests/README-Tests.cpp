#include <iostream>
#include <vector>
#include <complex>
#include "../src/Headers/FilesManager.hpp"

using namespace std;
using namespace FilesApi;

int main() {
    /// Simple use - write and read single simple value using operators
    /*FilesManager fm;
    fm.add("fileID", "../TestFiles/test_file.bin");
    int a = 12, b;
    fm.get("fileID").write(&a);
    fm.get("fileID").read(&b);
    cout << b << endl; // 12*/

    /// Simple use - write and read single simple value using operators
    /*FilesManager fm;
    fm["fileID"] = "../TestFiles/test_file.bin";
    int a = 12, b;
    fm["fileID"] << rw_t<int>(&a, 1);
    fm["fileID"] >> rw_t<int>(&b, 1);
    cout << b << endl; // 12*/

    /// Simple use - write and read single vector using operators
    /*FilesManager fm;
    fm["fileID"] = "../TestFiles/test_file.bin";
    vector<int> a = {1, 2, 3};
    vector<int> b(a.size());
    fm["fileID"] << a;
    fm["fileID"] >> b;
    for (auto& val : b) {
        cout << val << " ";
    } // 1 2 3*/

    /// Simple use - remove file from manager object
    /*FilesManager fm(false, 0, "../TestFiles/");
    //fm.add("5", "../TestFiles/test_file.bin"); // Add file to collection
    fm += add_data("5", "test_file.bin");
    int a = 12;
    int b;
    fm.get("5") << rw_t<int>(&a, 1); // Work
    fm.get("5").write(&a); // Work
    fm.get("5") >> rw_t<int>(&b, 1); // Work
    cout << b << endl; // Prints 12
    //fm.remove("5"); // Remove the file from collection
    fm -= "5"; // Remove the file from collection
    fm.get("5") << rw_t<int>(&a, 1); // Error
    fm.get("5").write(&a); // Error
    fm.get("5") >> rw_t<int>(&b, 1); // Error*/

    /// Use case - Insert multiple data to file and read into array
    /*FilesManager fm(false, 0, "../TestFiles/");
    fm += add_data("2", "test_file.bin");
    fm["2"].init_read_write_mode(ReadWriteMode::MULTIPLE);
    const size_t array_size = 100;
    for (size_t i = 0; i < array_size; i++) {
        fm["2"].write(&i);
    }
    size_t b[array_size];
    fm["2"].init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
    fm["2"] >> rw_t<size_t>(b, array_size);
    for (size_t i = 0; i < array_size; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
    vector<size_t> c(array_size);
    fm["2"] >> c;
    for (size_t i = 0; i < array_size; i++) {
        cout << c[i] << " ";
    }*/
    return 0;
}