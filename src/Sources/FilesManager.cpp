#include "../Headers/FilesManager.hpp"

namespace FilesApi {
    FilesManager::FilesManager(bool exceptions, size_t max_files, const std::string &files_path)
            : max_files(max_files), files_path(files_path), use_exceptions(exceptions) {
    }

    void FilesManager::add(const std::string &id, const std::string &file) {
        remove_unusable_files();
        if (max_files == 0 || files.size() + 1 < max_files) {
            files.insert(std::pair<std::string,
                    std::shared_ptr<File>>(id, std::make_shared<File>(file, use_exceptions, files_path)));
        }
    }

    void FilesManager::remove(const std::string &id) {
        remove_unusable_files();
        files.erase(id);
    }

    File &FilesManager::get(const std::string &id) {
        remove_unusable_files();
        File *ret_file = files[id].get();
        if (ret_file == nullptr) {
            files[id] = std::make_shared<File>("", use_exceptions, files_path);
            ret_file = files[id].get();
        }
        return *ret_file;
    }

    void FilesManager::operator+=(const add_data &data) {
        add(std::get<0>(data), std::get<1>(data));
    }

    File &FilesManager::operator[](const std::string &id) {
        return get(id);
    }

    void FilesManager::operator-=(const std::string &id) {
        remove(id);
    }

    void FilesManager::remove_unusable_files() {
        for (auto &file : files) {
            if (file.second && !file.second->is_file_ready()) {
                files.erase(file.first);
            }
        }
    }
}