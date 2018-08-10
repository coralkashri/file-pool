//
// Created by sherksecret on 8/10/18.
//

#ifndef FILESAPI_FILE_H
#define FILESAPI_FILE_H

#include <iostream>
#include <mutex>

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

enum class FileMode {
    ALWAYS_OPEN,
    OPEN_IN_ACTION
};

class File {
private:
    std::string         name;
    FileMode            file_mode;
    ReadWriteMode       read_write_mode;
    std::mutex          read_write_mutex;

    void change_rwm(ReadWriteMode new_rwm); // Change read/write mode

public:
    File(const std::string &file_path);
};


#endif //FILESAPI_FILE_H