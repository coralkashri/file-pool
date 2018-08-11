//
// Created by sherksecret on 8/10/18.
//

#include "File.h"

File::File(const std::string &file_path) {
    name = file_path;
}

File::~File() {
    std::lock_guard<std::mutex> guard(read_write_mutex);
    close();
}

void File::open(std::ios_base::openmode mode_flags, const FileAction &new_file_action) {
    std::lock_guard<std::mutex> guard(read_write_mutex);
    if (file_action != new_file_action) {
        file_ptr.close();
        if (file_action != FileAction::NONE) {
            std::cout << DesignText::make_colored("Pay attention: file mission replaced by another one.", DesignText::Color::RED, true) << std::endl;
        }
    }
    file_action = new_file_action;

    if (!file_ptr.is_open()) {
        file_ptr.open(name, mode_flags);
        if (file_ptr.fail()) {
            std::cout << DesignText::make_colored("Error Opening file: " + name, DesignText::Color::RED, true) << std::endl;
            // todo:: Throw an exception
        }
    }
}

void File::close(bool automatic) {
    if (!automatic || file_mode == FileMode::OPEN_IN_ACTION) {
        if (file_ptr.is_open()) {
            file_ptr.close();
            read_write_mode = ReadWriteMode::DONE;
            file_action = FileAction::NONE;
            std::cout << DesignText::make_colored("File has safely closed.", DesignText::Color::GREEN, false) << std::endl;
        }
    }
}

void File::close() {
    close(false);
}

void File::update_rwm() {
    switch (read_write_mode) {
        case ReadWriteMode::SINGLE_AND_DONE:
        case ReadWriteMode::DONE:
            read_write_mode = ReadWriteMode::DONE;
            file_action = FileAction::NONE;
            close(true);
            break;
        case ReadWriteMode::SINGLE_AND_MORE:
            read_write_mode = ReadWriteMode::SINGLE_AND_DONE;
            break;
        case ReadWriteMode::MULTIPLE:
            break;
    }
}

void File::init_read_write_mode(const ReadWriteMode &new_mode) {
    read_write_mode = new_mode;
}

//template File& File::write<int>(const int &val, size_t data_size, std::ios_base::openmode mode_flags);
//template File& File::read<int>(int &val, size_t data_size, std::ios_base::openmode mode_flags);