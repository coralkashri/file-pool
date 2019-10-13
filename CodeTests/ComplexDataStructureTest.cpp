#include <iostream>
#include <complex>
#include <boost/numeric/ublas/matrix.hpp>
#include "../src/File.hpp"

using namespace std;
using namespace FilesApi;
using namespace boost::numeric::ublas;

int mainComplexDataStructureTest() {
    File f("../TestFiles/test_file.bin");
    matrix<complex<float>> wdata(10, 5);
    matrix<complex<float>> rdata(wdata.size1(), wdata.size2());

    //f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE); // not necessary
    //f.write(wdata, wdata.size1() * wdata.size2());
    //f.init_read_write_mode(ReadWriteMode::SINGLE_AND_DONE); // not necessary
    //f.read(rdata, rdata.size1() * rdata.size2());

    for (size_t i = 0; i < rdata.size1(); i++) {
        for (size_t k = 0; k < rdata.size2(); k++) {
            cout << rdata(i, k) << "\t\t";
        }
        cout << endl;
    }
}