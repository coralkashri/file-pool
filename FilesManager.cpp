#include "FilesManager.h"

FilesManager::FilesManager(size_t max_files, const std::string &files_path) : max_files(max_files), files_path(files_path) {
}

void FilesManager::add(const std::string &id, const std::string &file) {
    if (max_files == 0 || files.size() + 1 < max_files) {
        std::string file_path;
        file_path = files_path == "" ? file : files_path + file;
        files.insert(std::pair<std::string, std::shared_ptr<File>>(id, std::make_shared<File>(file_path)));
    }
}

void FilesManager::remove(const std::string &id) {
    files.erase(id);
}

File& FilesManager::get(const std::string &id) {
    std::shared_ptr<File> f = files[id];
    return *f;
}
