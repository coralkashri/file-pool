#include <iostream>
#include <vector>
#include <complex>
#include "../src/FilesManager.hpp"

using namespace std;
using namespace FilesApi;

int main/*README_Tests*/() {
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
    //fm["fileID"] << rw_s<int>(&a, 1);
    //fm["fileID"] << rw_soft(&a, 1);
    fm["fileID"] << rw_soft(a, 1);
    //fm["fileID"] >> rw_s<int>(&b, 1);
    //fm["fileID"] >> rw_soft(&b, 1);
    fm["fileID"] >> rw_soft(b, 1);
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
    fm.get("5") << rw_soft(a); // Work
    fm.get("5").write(&a); // Work
    fm.get("5") >> rw_soft(b); // Work
    cout << b << endl; // Prints 12
    //fm.remove("5"); // Remove the file from collection
    fm -= "5"; // Remove the file from collection
    fm.get("5") << rw_soft(a); // Error
    fm.get("5").write(&a); // Error
    fm.get("5") >> rw_soft(b); // Error*/

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
    // Option 1
    //fm["2"] >> rw_soft(b, array_size);
    // Option 2
    //fm["2"] >> rw_soft(*b, array_size);
    // Option 3
    //fm["2"] >> rw_soft(b[0], array_size);
    // Option 4 - Read with offset from the array
    size_t offset = 5;
    for (size_t i = 0; i < offset; i++) {
        /// Fill the offset places in the array ahead, and see that they stay as they are.
        b[offset - i - 1] = array_size - 1 - i;
    }
    fm["2"] >> rw_soft(b[offset], array_size - offset);
    for (size_t i = 0; i < array_size; i++) {
        cout << b[i] << " ";
    } // 0...99 (Or with offset - 0...(99-offset))
    cout << endl;
    vector<size_t> c(array_size);
    fm["2"] >> c;
    for (size_t i = 0; i < array_size; i++) {
        cout << c[i] << " ";
    }*/
    return 0;
}