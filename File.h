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
 * SINGLE_AND_MORE - read/write single time, but don't close the file yet. wait for SINGLE_AND_DONE mode.
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
    void change_rwm(const ReadWriteMode &new_rwm); // Change read mode

public:
    File(const std::string &file_path);
    template<typename T> File& read(T &val, const ReadWriteMode &read_mode);
    template<typename T> File& write(const T &val, const ReadWriteMode &write_mode, std::ios_base::openmode mode_flags = std::ios_base::out | std::ios_base::app);
};


#endif //FILESAPI_FILE_H