//
// Created by sherksecret on 8/10/18.
//

#ifndef FILESAPI_FILE_H
#define FILESAPI_FILE_H

#include <iostream>
#include <mutex>
#include <fstream>

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
    std::string         name;
    FileMode            file_mode = FileMode::OPEN_IN_ACTION;
    ReadWriteMode       read_write_mode = ReadWriteMode::DONE;
    FileAction          file_action = FileAction::NONE;
    std::mutex          read_write_mutex;
    std::fstream        file_ptr;

    void open(std::ios_base::openmode mode_flags, const FileAction &new_file_action);
    void update_rwm(); // Change read mode
    void close(bool automatic);
public:
    File(const std::string &file_path);
    ~File();
    void close();
    void init_read_write_mode(const ReadWriteMode &read_mode);

    template<typename T>
    File& read(T &val, const size_t data_size, std::ios_base::openmode mode_flags = std::ios_base::in) {
        open(mode_flags, FileAction::READ);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.read((char*)(&val), data_size);

        update_rwm();
        return *this;
    }

    template<typename T>
    File& write(const T &val, const size_t data_size, std::ios_base::openmode mode_flags = std::ios_base::out | std::ios_base::app) {
        open(mode_flags, FileAction::WRITE);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.write((char*)(&val), data_size);

        update_rwm();
        return *this;
    }
};

#endif //FILESAPI_FILE_H