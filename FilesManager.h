#ifndef FILESAPI_FILESMANAGER_H
#define FILESAPI_FILESMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "File.h"

using add_data = std::tuple<const std::string&, const std::string&>;

class FilesManager {
private:
    std::map<std::string, std::shared_ptr<File>>    files;
    size_t                                          max_files; // zero for unlimited
    std::string                                     files_path; // Leave "" if there is no single path for all of the files
    //todo:: Add flag: "use_exceptions" - if true- exceptions will be thrown. else- only red colored messages. (Pass this value to every new File object).

    void remove_unusable_files();

public:
    explicit FilesManager(size_t max_files = 0, const std::string &files_path = "");
    void add(const std::string &id, const std::string &file);

    // todo:: Check this method.
    void remove(const std::string &id);

    // todo:: Check this method.
    File& get(const std::string &id);

    /**
     * Add new file
     * @param data - tuple(0) => file id. tuple(1_ => file name or path (if files path is "").
     */
    // todo:: Check this method.
    void operator+=(const add_data& data);

    /**
     * Get file
     * @param id - file's id
     */
    // todo:: Check this method.
    File& operator[](const std::string &id);

    /**
     * Remove file
     * @param id - file's id
     */
    // todo:: Check this method.
    void operator-=(const std::string &id);
};


#endif //FILESAPI_FILESMANAGER_H