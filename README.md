# FilesApi C++
filesApi gives you an easy files collection manager, which take care for all of ifstream, ofstream issues. An easy way to read and write complex and simple structures to files in C++.

## OS
This API built in linux os (ubuntu 16.04) and haven't been checked on other OS.

## Examples
#### Simple use - write and read single simple value
Init FilesManager object:
```cpp
FilesManager fm;
fm.add("fileID", "../TestFiles/test_file.bin");
```
Write data
```cpp
int a = 12, b;
fm.get("fileID").write(&a);
```
Read data
```cpp
fm.get("fileID").read(&b);
cout << b << endl; // 12
```

#### Simple use - write and read single simple value using operators
Init FilesManager object:
```cpp
FilesManager fm;
fm["fileID"] = "../TestFiles/test_file.bin";
```
Write data
```cpp
int a = 12, b;
//Option 1
fm["fileID"] << rw_s<int>(&a/*, 1 <default is 1>*/);
//Option 2
fm["fileID"] << rw_s<int>(a);
//Option 3
fm["fileID"] << rw_soft(&a);
//Option 4 (Recommended)
fm["fileID"] << rw_soft(a);
```
Read data
```cpp
// As same as Write, but with operator >>
fm["fileID"] >> rw_soft(b);
cout << b << endl; // 12
```

#### Simple use - write and read single vector using operators
Write data
```cpp
vector<int> a = {1, 2, 3};
vector<int> b(a.size());
fm["fileID"] << a;
```
Read data
```cpp
fm["fileID"] >> b;
for (auto& val : b) {
    cout << val << " ";
} // 1 2 3
```

#### Simple use - remove file from manager object
Insert file to manager
```cpp
FilesManager fm;
fm.add("5", "../TestFiles/test_file.bin");
```
Write/Read methods
```cpp
int a = 12;
int b;
fm.get("5") << rw_soft(a); // Work
fm.get("5").write(&a); // Work
fm.get("5") >> rw_soft(b); // Work
cout << b << endl; // Prints 12
```
Remove file from manager
```cpp
fm.remove("5");
```
Try Write/Read methods
```cpp
fm.get("5") << rw_soft(a); // Error
fm.get("5").write(&a); // Error
fm.get("5") >> rw_soft(b); // Error
```

#### Simple use - remove file from manager object using operators
Insert file to manager
```cpp
FilesManager fm(false, 0, "../TestFiles/");
fm += add_data("5", "test_file.bin");
```
Remove file from manager
```cpp
fm -= "5";
```

#### Use case - Insert multiple data to file and read into array or into vector
Write data to file
```cpp
fm["2"].init_read_write_mode(ReadWriteMode::MULTIPLE);
const size_t array_size = 100;
for (size_t i = 0; i < array_size; i++) {
    fm["2"] << rw_soft(i);
}
```
Read data to array
```cpp
size_t b[array_size];
fm["2"].init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE);
// Option 1
fm["2"] >> rw_soft(b, array_size);
// Option 2
fm["2"] >> rw_soft(*b, array_size);
// Option 3
fm["2"] >> rw_soft(b[0], array_size);
// Option 4 - Read with offset from the array
size_t offset = 5;
fm["2"] >> rw_soft(b[offset], array_size - offset);
for (size_t i = 0; i < array_size; i++) {
    cout << b[i] << " ";
} // 0...99 (Or with offset - 0...(99-offset))
```
Read data to vector
```cpp
vector<size_t> c(array_size);
fm["2"] >> c;
for (size_t i = 0; i < array_size; i++) {
    cout << c[i] << " ";
} // 0...99
```

#### Use case - Write and read vector of vectors
Init vectors
```cpp
File f("../TestFiles/test_file.bin");
vector<vector<complex<float>>> wdata = {
        {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
        {{1, 2}, {3, 4},  {5,      6},    {7,     8.156}},
        {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
        {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
        {{1, 9}, {3, 75}, {213.34, 21.4}, {153.1, 15.85}},
        {{1, 9}, {3, 75}, {9999,   21.4}, {153.1, 15.85}},
        {{1, 2}, {3, 4},  {5,      6},    {7,     8.156}}
};
vector<vector<complex<float>>> rdata(wdata.size());
for (size_t i = 0; i < wdata.size(); i++) {
    rdata[i] = vector<complex<float>>(wdata[i].size());
}
```
Write to file
```cpp
//f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE); // not necessary
f << wdata;
```
Read from file
```cpp
//f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE); // not necessary
f >> rdata;
```
Print values
```cpp
for (size_t i = 0; i < rdata.size(); i++) {
    for (size_t k = 0; k < rdata[i].size(); k++) {
        cout << rdata[i][k] << endl;
    }
}
```