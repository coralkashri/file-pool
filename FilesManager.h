#ifndef FILESAPI_FILESMANAGER_H
#define FILESAPI_FILESMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "File.h"

class FilesManager {
private:
    std::map<std::string, std::shared_ptr<File>>    files;
    size_t                                          max_files; // zero for unlimited
    std::string                                     files_path; // Leave "" if there is no single path for all of the files

public:
    FilesManager(size_t max_files = 0, const std::string &files_path = "");
    void add(const std::string &id, const std::string &file);
    void remove(const std::string &id);
    File& get(const std::string &id);
};


#endif //FILESAPI_FILESMANAGER_H