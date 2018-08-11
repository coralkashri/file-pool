//
// Created by sherksecret on 8/10/18.
//

#include "File.h"

File::File(const std::string &file_path) {

}

void File::open(std::ios_base::openmode mode_flags, const FileAction &new_file_action) {
    std::lock_guard<std::mutex> guard(read_write_mutex);
    if (file_action != new_file_action) {
        file_ptr.close();
        std::cerr << "Pay attention: file mission replaced by another one." << std::endl;
    }
    file_action = new_file_action;

    if (!file_ptr.is_open()) {
        file_ptr.open(name, mode_flags);
        if (file_ptr.fail()) {
            std::cerr << "Error Opening file: " << name << std::endl;
            // todo:: Throw an exception
        }
    }
}

void File::change_rwm(const ReadWriteMode &new_rwm) {
    std::lock_guard<std::mutex> guard(read_write_mutex);
}

template<typename T>
File &File::read(T &val, const ReadWriteMode &read_mode) {
    std::lock_guard<std::mutex> guard(read_write_mutex);
    return *this;
}

template<typename T>
File &File::write(const T &val, const ReadWriteMode &write_mode, std::ios_base::openmode mode_flags) {
    change_rwm(write_mode);
    open(mode_flags, FileAction::WRITE);
    std::lock_guard<std::mutex> guard(read_write_mutex);

    switch (write_mode) {
        case ReadWriteMode::MULTIPLE:
            break;
    }

    return *this;
}
