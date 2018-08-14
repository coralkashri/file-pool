#include "File.h"

File::File(const std::string &file_path) {
    name = file_path;
    is_open = false;
    file_mode = FileMode::OPEN_IN_ACTION;
    read_write_mode = ReadWriteMode::DONE;
    file_action = FileAction::NONE;
    write_flags = std::ios::out | std::ios::binary | std::ios::in;
    read_flags = std::ios_base::in;
}

File::~File() {
    std::lock_guard<std::mutex> guard(read_write_mutex);
    close();
}

void File::open(std::ios_base::openmode mode_flags, const FileAction &new_file_action) {
    std::lock_guard<std::mutex> guard(read_write_mutex);
    if (file_action != new_file_action) {
        file_ptr.close();
        is_open = false;
        if (file_action != FileAction::NONE) {
            std::cout << DesignText::make_colored("Pay attention: file mission replaced by another one. (file closed)", DesignText::Color::RED, true) << std::endl;
        }
    }
    file_action = new_file_action;

    if (!is_open) {
        file_ptr.open(name, mode_flags);
        std::cout << DesignText::make_colored("File has safely opened.", DesignText::Color::GREEN, false) << std::endl;
        is_open = true;
        if (file_ptr.fail()) {
            is_open = false;
            std::cout << DesignText::make_colored("Error Opening file: " + name, DesignText::Color::RED, true) << std::endl;
            // todo:: Throw an exception
        }
    }
}

void File::close(bool automatic) {
    if ((!automatic) || (file_mode == FileMode::OPEN_IN_ACTION)) {
        if (is_open) {
            file_ptr.close();
            is_open = false;
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
            close(true);
            break;
        case ReadWriteMode::SINGLE_AND_MORE:
            read_write_mode = ReadWriteMode::SINGLE_AND_DONE;
            break;
        case ReadWriteMode::MULTIPLE:
            if (multiple_times_left > -1 && !--multiple_times_left) {
                multiple_times_left = -1;
                close(true);
            }
            break;
    }
}

void File::init_read_write_mode(const ReadWriteMode &new_mode, const int multiple_times) {
    read_write_mode = new_mode;
    multiple_times_left = multiple_times;
}

void File::init_read_flags(const std::ios_base::openmode new_read_flags) {
    read_flags = new_read_flags;
}

void File::init_write_flags(const std::ios_base::openmode new_write_flags) {
    write_flags = new_write_flags;
}

//template File& File::write<int>(const int &val, size_t data_size, std::ios_base::openmode mode_flags);
//template File& File::read<int>(int &val, size_t data_size, std::ios_base::openmode mode_flags);