#ifndef FILESAPI_FILEWRAPPERS_H
#define FILESAPI_FILEWRAPPERS_H

#include <iostream>
#include <boost/assert.hpp>

namespace FilesApi {
    /// Use in read/write for non-array overload operator. e.g: file >> rw_s<T>{val};
    template<typename T>
    struct rw_s {
        T*          val;

        explicit rw_s(T &value) : val(&value) {}

        explicit rw_s(T *value) : val(value) {
            assert(value != nullptr);
        }
    };

    /// Use in read/write for arrays overload operator. e.g: file >> rw_s<T>{arr, 10};
    template<typename T>
    struct rw_s_array {
        T*          val;
        size_t      val_size;

        explicit rw_s_array(T &value, size_t arr_size) : val(&value), val_size(arr_size) {
            assert(arr_size > 0);
        }

        explicit rw_s_array(T *value, size_t arr_size) : val(value), val_size(arr_size) {
            assert(arr_size > 0);
            assert(value != nullptr);
        }
    };
}

namespace FilesApi {
    /**
     * Wrapper functions for rw_t object creation, without need to specify the type after the function's name
     * Instead of call:    f << rw_t<int>(a);
     * Call:               f << rw_soft(a);
    */
    template<typename T>
    rw_s<T> rw_soft(T &value) {
        return rw_s<T>(value);
    }

    template<typename T>
    rw_s<T> rw_soft(T *value) {
        return rw_soft(*value);
    }

    template<typename T>
    rw_s_array<T> rw_soft_array(T &value, size_t arr_size) {
        return rw_s_array<T>(value, arr_size);
    }

    template<typename T>
    rw_s_array<T> rw_soft_array(T *value, size_t arr_size) {
        return rw_soft_array(*value, arr_size);
    }
}

#endif //FILESAPI_FILEWRAPPERS_H
