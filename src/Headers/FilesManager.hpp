#ifndef FILESAPI_FILESMANAGER_H
#define FILESAPI_FILESMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "File.hpp"

namespace FilesApi {
    using add_data = std::tuple<const std::string, const std::string>;

    class FilesManager {
    private:
        std::map<std::string, std::shared_ptr<File>> files;
        size_t max_files; // zero for unlimited
        std::string files_path; // Leave "" if there is no single path for all of the files
        bool use_exceptions;

        void remove_unusable_files();

    public:
        /**
         * Ctor
         * @param exceptions - Throw exceptions on errors Or use bold cout messages.
         * @param max_files - Maximum files number to manage in this FilesManager object (0 for unlimited).
         * @param files_path - if @param files_path == "" => in new file associate you will have to supply full
         *                  file path, e.g: "path/to/file/filename.bin"
         *                  else supply only file name, e.g: "filename.bin", if @param files_path == "path/to/file/"
         */
        explicit FilesManager(bool exceptions = false, size_t max_files = 0, const std::string &files_path = "");

        /**
         * Add new file
         * @param id - file id (will be use to get this File object).
         * @param file - file's name or path (if @files_path == "").
         */
        void add(const std::string &id, const std::string &file);

        /**
         * Remove file
         * @param id - file's id
         */
        void remove(const std::string &id);

        /**
         * Get file
         * @param id - file's id
         */
        File &get(const std::string &id);

        /**
         * Add new file
         * @param data - tuple(0) => file id. tuple(1_ => file name or path (if files path is "").
         */
        void operator+=(const add_data &data);

        /**
         * Get file
         * @param id - file's id
         */
        File &operator[](const std::string &id);

        /**
         * Remove file
         * @param id - file's id
         */
        void operator-=(const std::string &id);
    };
}
#endif //FILESAPI_FILESMANAGER_H