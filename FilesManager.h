//
// Created by sherksecret on 8/10/18.
//

#ifndef FILESAPI_FILESMANAGER_H
#define FILESAPI_FILESMANAGER_H

#include <iostream>
#include <vector>
#include "File.h"

class FilesManager {
private:
    std::vector<File>           files;
    size_t                      max_files; // zero for unlimited
    std::string                 files_path; // Leave "" if there is no single path for all of the files

public:
    FilesManager(size_t max_files, const std::string &files_path);
    File& get(size_t number);
};


#endif //FILESAPI_FILESMANAGER_H
