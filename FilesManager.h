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
    std::vector<File>         files;


public:

    File& get(size_t number);
};


#endif //FILESAPI_FILESMANAGER_H
