#ifndef FILESAPI_FILE_H
#define FILESAPI_FILE_H

#include <iostream>
#include <mutex>
#include <fstream>
#include <vector>
#include "DesignText.h"

/// Use in read/write for non-vectors overload operator. e.g: file >> rw_t<T>{val, 1, std::ios_base::in};
template<typename T> using rw_t = std::tuple<T*, const size_t&>;


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
    std::string             name;
    FileMode                file_mode;
    ReadWriteMode           read_write_mode;
    FileAction              file_action;
    std::mutex              read_write_mutex;
    std::fstream            file_ptr;
    bool                    is_open;
    std::ios_base::openmode read_flags;
    std::ios_base::openmode write_flags;

    void open(std::ios_base::openmode mode_flags, const FileAction &new_file_action);
    void update_rwm(); // Change read mode
    void close(bool automatic);

public:
    File(const std::string &file_path);
    ~File();
    void close();
    void init_read_write_mode(const ReadWriteMode &read_mode);
    void init_read_flags(std::ios_base::openmode read_flags = std::ios_base::in);
    void init_write_flags(std::ios_base::openmode write_flags = std::ios::out | std::ios::binary | std::ios::in);

    template<typename T> File& read(T *val, size_t data_size = 1);

    /**
     * Read to vector
     * @tparam T - vector type
     * @param val - vector to read into (Have to be initialize with the size of inputs' count).
     * @param mode_flags - fstream open flags
     * @return
     */
    template<typename T> File& read(std::vector<T> &val);
    template<typename T> File& write(const T *val, size_t data_size = 1);
    template<typename T> File& write(const std::vector<T> &val);

    /**
     * Read to vector
     * @tparam T - vector type
     * @param info - tuple(0)=> vector to read into, tuple(1)=> fstream open flags
     * @return
     */
    template<typename T> File& operator>>(std::vector<T>& data);

    /**
     * Read to non-vector
     * @tparam T - variable type
     * @param info - tuple(0)=> variable non-vector to read into, tuple(1)=> in case of array- array's size (else write 1), tuple(2)=> fstream open flags
     * @return
     */
    template<typename T> File& operator>>(const rw_t<T> &info);

    /**
     * Write vector to file
     * @tparam T - vector type
     * @param info - tuple(0)=> vector to write, tuple(1)=> fstream open flags
     * @return
     */
    template<typename T> File& operator<<(const std::vector<T>& data);

    /**
     * Write non-vector to file
     * @tparam T - variable type
     * @param info - tuple(0)=> variable non-vector to read into, tuple(1)=> in case of array- array's size (else write 1), tuple(2)=> fstream open flags
     * @return
     */
    template<typename T> File& operator<<(const rw_t<T> &info);
};

template<typename T> File& File::read(T *val, const size_t data_size) {
    open(read_flags, FileAction::READ);
    std::lock_guard<std::mutex> guard(read_write_mutex);

    file_ptr.read((char*)(val), sizeof(T) * data_size);

    update_rwm();
    return *this;
}

template<typename T> File& File::write(const T *val, const size_t data_size) {
    open(write_flags, FileAction::WRITE);
    std::lock_guard<std::mutex> guard(read_write_mutex);

    file_ptr.write(reinterpret_cast<const char*>(val), sizeof(T) * data_size);

    update_rwm();
    return *this;
}

template<typename T> File& File::read(std::vector<T> &val) {
    open(read_flags, FileAction::READ);
    std::lock_guard<std::mutex> guard(read_write_mutex);

    file_ptr.read(reinterpret_cast<char*>(val.data()), sizeof(T) * val.size());

    update_rwm();
    return *this;
}

template<typename T> File& File::write(const std::vector<T> &val) {
    open(write_flags, FileAction::WRITE);
    std::lock_guard<std::mutex> guard(read_write_mutex);

    file_ptr.write(reinterpret_cast<const char*>(val.data()), sizeof(T) * val.size());

    update_rwm();
    return *this;
}

template<typename T> File& File::operator>>(std::vector<T>& data) {
    return read(data);
}

template<typename T> File &File::operator>>(const rw_t<T> &info) {
    return read(std::get<0>(info), std::get<1>(info));
}

template<typename T> File &File::operator<<(const std::vector<T>& data) {
    return write(data);
}

template<typename T> File &File::operator<<(const rw_t<T> &info) {
    return write(std::get<0>(info), std::get<1>(info));
}

#endif //FILESAPI_FILE_H