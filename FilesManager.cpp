#include "FilesManager.h"

FilesManager::FilesManager(size_t max_files, const std::string &files_path) : max_files(max_files), files_path(files_path) {
}

void FilesManager::add(const std::string &id, const std::string &file) {
    // todo:: If there is value in this->files_path variable use it before the file name in the add operation,
    if (max_files == 0 || files.size() + 1 < max_files) {
        files.insert(std::pair<std::string, std::shared_ptr<File>>(id, std::make_shared<File>(file, files_path)));
    }
}

void FilesManager::remove(const std::string &id) {
    remove_unusable_files();
    files.erase(id);
}

File& FilesManager::get(const std::string &id) {
    std::shared_ptr<File> f = files[id];
    return *f;
}

void FilesManager::operator+=(const add_data &data) {
    remove_unusable_files();
    add(std::get<0>(data), std::get<1>(data));
}

File& FilesManager::operator[](const std::string &id) {
    remove_unusable_files();
    File *ret_file = nullptr;
    ret_file = files[id].get();
    if (ret_file == nullptr) {
        add(id, "");
        ret_file = files[id].get();
    }
    return *ret_file;
}

void FilesManager::operator-=(const std::string &id) {
    remove(id);
}

void FilesManager::remove_unusable_files() {
    for (auto& file : files) {
        if (!file.second->is_file_ready()) {
            files.erase(file.first);
        }
    }
}