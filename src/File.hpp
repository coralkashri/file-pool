#ifndef FILESAPI_FILE_H
#define FILESAPI_FILE_H

#include <iostream>
#include <mutex>
#include <fstream>
#include <vector>
#include <boost/assert.hpp>
#include "extentions/std_extentions.h"
#include "FileWrappers.h"
#include "utilities/DesignText.hpp"
#include "utilities/Exceptions.hpp"

namespace FilesApi {

    /**
     * >> if file_mode is OPEN_IN_ACTION:
     * SINGLE_AND_DONE - read/write single time, and then close the file.
     * SINGLE_AND_MORE - read/write single time, but don't close the file yet. After single read/write the mode will automatic update to SINGLE_AND_DONE mode.
     * MULTIPLE - close the file only in programmer order, until then the file will be remain open.
     */
    enum class ReadWriteMode {
        SINGLE_AND_DONE,
        SINGLE_AND_MORE,
        MULTIPLE,
        DONE
    };

    enum class FileAction {
        READ,
        WRITE,
        NONE
    };

    enum class FileMode {
        ALWAYS_OPEN,
        OPEN_IN_ACTION
    };

    class File {
    private:
        bool is_ready;
        std::string name;
        std::string path;
        FileMode file_mode;
        ReadWriteMode read_write_mode;
        int multiple_times_left;
        FileAction file_action;
        std::mutex read_write_mutex;
        std::fstream file_ptr;
        bool is_open;
        std::ios_base::openmode read_flags;
        std::ios_base::openmode write_flags;
        bool use_exceptions;

        /**
         * Open file in specific format
         * \param mode_flags - fstream.open() flags.
         * \param new_file_action - Open purpose.
         */
        void open(std::ios_base::openmode mode_flags, const FileAction &new_file_action);

        /**
         * Auto update for the file's mode (READ / WRITE / NONE).
         */
        void update_rwm();

        /**
         * Close file
         * \param automatic - Close request from API(true) or from User(false)
         */
        void close(bool automatic);

        /**
         * Is file ready for read/write actions. Exception if file not ready.
         * \return Is file name not empty.
         */
        bool is_file_ready(int);

    public:
        /**
         * Ctor
         * \param file_name     - if @param file_path == "" => path/to/file/filename.bin else filename.bin
         * \param exceptions    - Throw exceptions on errors Or use bold cout messages.
         * \param file_path     - file's path.
         */
        explicit File(const std::string &file_name, bool exceptions = false, const std::string &file_path = "");

        /**
         * Close the file.
         */
        ~File();

        /**
         * Force close the file.
         */
        void close();

        /**
         * Set file's name.
         * \param new_name - New file's name.
         */
        void set_name(const std::string &new_name);

        /**
         * Set file's name.
         * \param new_name - New file's name.
         */
        File &operator=(const std::string &new_name);

        /**
         * Get file's name
         * \return File's name.
         */
        std::string get_name();

        /**
         * Is file ready for read/write actions. Without exception if file not ready.
         * \return Is file name not empty.
         */
        bool is_file_ready();

        /**
         * Init current file's mode
         * \param mode - How much reads/writes until the file will close.
         * \param multiple_times - if mode is multiple note how much times (-1 for unknown - won't close the file without programmer order/interrupt).
         */
        void init_read_write_mode(const ReadWriteMode &mode, int multiple_times = -1);

        /**
         * Init read fstream flags.
         * \param read_flags - When open function in read mode will occur, those flags will be in use.
         */
        void init_read_flags(std::ios_base::openmode read_flags = std::ios_base::in);

        /**
         * Init write fstream flags.
         * \param write_flags - When open function in write mode will occur, those flags will be in use.
         */
        void init_write_flags(std::ios_base::openmode write_flags = std::ios::out | std::ios::binary | std::ios::in);

        /**
         * Read to array variable
         * \param T - variable type
         * \param val - variable address
         * \param data_size - array's size.
         * \return this File object.
         */
        template<class T>
        File &read_array(T *val, size_t data_size);

        /**
         * Read to non-array variable
         * \param T - variable type
         * \param val - variable address
         * \return this File object.
         */
        template<class T>
        File &read(T *val);

        /**
         * Read to vector variable
         * \tparam T - vector type
         * \param val - vector to read into (Have to be initialize with the size of inputs' count).
         * \param data_size - vector to read into (Have to be initialize with the size of inputs' count).
         * \return this File object.
         */
        template<template<class T> class Container, class T>
        File &read(Container<T> &val, size_t size);

        /**
         * Write array variable
         * \tparam T - variable type
         * \param val - variable address
         * \param data_size - array's size.
         * \return this File object.
         */
        template<class T>
        File &write_array(const T *val, size_t data_size);

        /**
         * Write non-array variable
         * \tparam T - variable type
         * \param val - variable address
         * \return this File object.
         */
        template<class T>
        File &write(const T *val);

        /**
         * Write vector variable
         * \tparam T - vector type
         * \param val - vector to write.
         * \return this File object.
         */
        template<template<class T> class Container, class T>
        File &write(const Container<T> &val, size_t size);

        /**
         * Read to vector
         * \tparam T - vector type
         * \param data - vector to read into
         * \return this File object.
         */
        template<template<class T> class Container, class T>
        File &operator>>(Container<T> &data);

        /**
         * Read to non-array
         * \tparam T - variable type
         * \param info - {
         *                  val - variable non-vector to read into
         *               }
         * \return this File object
         */
        template<class T>
        File &operator>>(const rw_s<T> &info);

        /**
         * Read to array
         * \tparam T - variable type
         * \param info - {
         *                  val - variable non-vector to read into
         *                  val_size - array's size
         *               }
         * \return this File object
         */
        template<class T>
        File &operator>>(const rw_s_array<T> &info);

        /**
         * Write vector to file
         * \tparam T - vector type
         * \param data - vector to write
         * \return this File object
         */
        template<template<class T> class Container, class T>
        File &operator<<(const Container<T> &data);

        /**
         * Write non-array to file
         * \tparam T - variable type
         * \param info - {
         *                  val - variable non-vector to write
         *               }
         * \return this File object
         */
        template<class T>
        File &operator<<(const rw_s<T> &info);

        /**
         * Write array to file
         * \tparam T - variable type
         * \param info - {
         *                  val - variable non-vector to write
         *                  val_size - array's size
         *               }
         * \return this File object
         */
        template<class T>
        File &operator<<(const rw_s_array<T> &info);
    };

    template<class T>
    File &File::read(T *val) {
        if (!is_file_ready(0)) {
            return *this;
        }
        static_assert(std::is_trivially_copyable_v<T>);
        open(read_flags, FileAction::READ);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.read(reinterpret_cast<char *>(val), sizeof(T));

        update_rwm();
        return *this;
    }

    template<class T>
    File &File::read_array(T *val, const size_t data_size) {
        if (!is_file_ready(0)) {
            return *this;
        }
        static_assert(std::is_trivially_copyable_v<T>);
        open(read_flags, FileAction::READ);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.read(reinterpret_cast<char *>(val), sizeof(T) * data_size);

        update_rwm();
        return *this;
    }

    template<class T>
    File &File::write(const T *val) {
        if (!is_file_ready(0)) {
            return *this;
        }
        static_assert(std::is_trivially_copyable_v<T>);
        open(write_flags, FileAction::WRITE);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.write(reinterpret_cast<const char *>(val), sizeof(T));

        update_rwm();
        return *this;
    }

    template<class T>
    File &File::write_array(const T *val, const size_t data_size) {
        if (!is_file_ready(0)) {
            return *this;
        }
        static_assert(std::is_trivially_copyable_v<T>);
        open(write_flags, FileAction::WRITE);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.write(reinterpret_cast<const char *>(val), sizeof(T) * data_size);

        update_rwm();
        return *this;
    }

    template<template<class T> class Container, class T>
    File &File::read(Container<T> &val, size_t size) {
        if (!is_file_ready(0)) {
            return *this;
        }
        static_assert(std::is_trivially_copyable_v<T>);
        static_assert(std::is_container<Container<T>>::value);
        open(read_flags, FileAction::READ);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.read(reinterpret_cast<char *>(val.data()), sizeof(T) * size);

        update_rwm();
        return *this;
    }

    template<template<class T> class Container, class T>
    File &File::write(const Container<T> &val, size_t size) {
        if (!is_file_ready(0)) {
            return *this;
        }
        static_assert(std::is_trivially_copyable_v<T>);
        static_assert(std::is_container<Container<T>>::value);
        open(write_flags, FileAction::WRITE);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.write(reinterpret_cast<const char *>(val.data()), sizeof(T) * size);

        update_rwm();
        return *this;
    }

    template<template<class T> class Container, class T>
    File &File::operator>>(Container<T> &data) {
        static_assert(std::is_container<Container<T>>::value);
        return read(data, data.size());
    }

    template<class T>
    File &File::operator>>(const rw_s<T> &info) {
        return read(info.val);
    }

    template<class T>
    File &File::operator>>(const rw_s_array<T> &info) {
        return read_array(info.val, info.val_size);
    }

    template<template<class T> class Container, class T>
    File &File::operator<<(const Container<T> &data) {
        static_assert(std::is_container<Container<T>>::value);
        return write(data, data.size());
    }

    template<class T>
    File &File::operator<<(const rw_s<T> &info) {
        return write(info.val);
    }

    template<class T>
    File &File::operator<<(const rw_s_array<T> &info) {
        return write_array(info.val, info.val_size);
    }
}

#endif //FILESAPI_FILE_H