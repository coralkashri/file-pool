#ifndef FILESAPI_FILE_H
#define FILESAPI_FILE_H

#include <iostream>
#include <mutex>
#include <fstream>
#include <vector>
#include <boost/assert.hpp>
#include "../utilities/DesignText.hpp"
#include "../utilities/Exceptions.hpp"

namespace FilesApi {

    /// Use in read/write for non-vectors overload operator. e.g: file >> rw_t<T>{val, 1};
    template<typename T> struct rw_s {
        T*          val;
        size_t      val_size;

        rw_s(T &value, size_t arr_size = 1) : val(&value), val_size(arr_size) {
            assert(arr_size > 0);

        }

        rw_s(T *value, size_t arr_size = 1) : val(value), val_size(arr_size) {
            assert(arr_size > 0);
            assert(value != nullptr);
        }
    };

    /// Wrapper function for creation of rw_t object, without need for specify the type after the function name
    /// Instead of call:    f << rw_t<int>(a, size);
    /// Call:               f << rw_soft(a, size);
    template<typename T> rw_s<T> rw_soft(T &value, size_t arr_size = 1) {
        return rw_s<T>(value, arr_size);
    }

    template<typename T> rw_s<T> rw_soft(T *value, size_t arr_size = 1) {
        return rw_soft(*value, arr_size);
    }

    /**
     * >> if file_mode is OPEN_IN_ACTION:
     * SINGLE_AND_DONE - read/write single time, and then close the file.
     * SINGLE_AND_MORE - read/write single time, but don't close the file yet. After single read/write the mode will automatic update to SINGLE_AND_DONE mode.
     * MULTIPLE - close the file only in programmer order, until then the file will be remain open.
     */
    enum class ReadWriteMode {
        SINGLE_AND_DONE,
        SINGLE_AND_MORE,
        MULTIPLE,
        DONE
    };

    enum class FileAction {
        READ,
        WRITE,
        NONE
    };

    enum class FileMode {
        ALWAYS_OPEN,
        OPEN_IN_ACTION
    };

    class File {
    private:
        bool is_ready;
        std::string name;
        std::string path;
        FileMode file_mode;
        ReadWriteMode read_write_mode;
        int multiple_times_left;
        FileAction file_action;
        std::mutex read_write_mutex;
        std::fstream file_ptr;
        bool is_open;
        std::ios_base::openmode read_flags;
        std::ios_base::openmode write_flags;
        bool use_exceptions;

        /**
         * Open file in specific format
         * \param mode_flags - fstream.open() flags.
         * \param new_file_action - Open purpose.
         */
        void open(std::ios_base::openmode mode_flags, const FileAction &new_file_action);

        /**
         * Auto update for the file's mode (READ / WRITE / NONE).
         */
        void update_rwm();

        /**
         * Close file
         * \param automatic - Close request from API(true) or from User(false)
         */
        void close(bool automatic);

        /**
         * Is file ready for read/write actions. Exception if file not ready.
         * \return Is file name not empty.
         */
        bool is_file_ready(int);

    public:
        /**
         * Ctor
         * \param file_name     - if @param file_path == "" => path/to/file/filename.bin else filename.bin
         * \param exceptions    - Throw exceptions on errors Or use bold cout messages.
         * \param file_path     - file's path.
         */
        explicit File(const std::string &file_name, bool exceptions = false, const std::string &file_path = "");

        /**
         * Close the file.
         */
        ~File();

        /**
         * Force close the file.
         */
        void close();

        /**
         * Set file's name.
         * \param new_name - New file's name.
         */
        void set_name(const std::string &new_name);

        /**
         * Set file's name.
         * \param new_name - New file's name.
         */
        File &operator=(const std::string &new_name);

        /**
         * Get file's name
         * \return File's name.
         */
        std::string get_name();

        /**
         * Is file ready for read/write actions. Without exception if file not ready.
         * \return Is file name not empty.
         */
        bool is_file_ready();

        /**
         * Init current file's mode
         * \param mode - How much reads/writes until the file will close.
         * \param multiple_times - if mode is multiple note how much times (-1 for unknown - won't close the file without programmer order/interrupt).
         */
        void init_read_write_mode(const ReadWriteMode &mode, int multiple_times = -1);

        /**
         * Init read fstream flags.
         * \param read_flags - When open function in read mode will occur, those flags will be in use.
         */
        void init_read_flags(std::ios_base::openmode read_flags = std::ios_base::in);

        /**
         * Init write fstream flags.
         * \param write_flags - When open function in write mode will occur, those flags will be in use.
         */
        void init_write_flags(std::ios_base::openmode write_flags = std::ios::out | std::ios::binary | std::ios::in);

        /**
         * Read to non-vector variable
         * \param T - variable type
         * \param val - variable address
         * \param data_size - in case of array- array's size.
         * \return this File object.
         */
        template<class T>
        File &read(T *val, size_t data_size = 1);

        /**
         * Read to vector variable
         * \tparam T - vector type
         * \param val - vector to read into (Have to be initialize with the size of inputs' count).
         * \param data_size - vector to read into (Have to be initialize with the size of inputs' count).
         * \return this File object.
         */
        template<class T>
        File &read(std::vector<T> &val);

        /**
         * Write non-vector variable
         * \tparam T - variable type
         * \param val - variable address
         * \param data_size - in case of array- array's size.
         * \return this File object.
         */
        template<class T>
        File &write(const T *val, size_t data_size = 1);

        /**
         * Write vector variable
         * \tparam T - vector type
         * \param val - vector to write.
         * \return this File object.
         */
        template<class T>
        File &write(const std::vector<T> &val);

        /**
         * Read to vector
         * \tparam T - vector type
         * \param data - vector to read into
         * \return this File object.
         */
        template<class T>
        File &operator>>(std::vector<T> &data);

        /**
         * Read to non-vector
         * \tparam T - variable type
         * \param info - {
         *                  val - variable non-vector to read into
         *                  val_size - in case of array- array's size (else leave as default 1)
         *               }
         * \return this File object
         */
        template<class T>
        File &operator>>(const rw_s<T> &info);

        /**
         * Write vector to file
         * \tparam T - vector type
         * \param data - vector to write
         * \return this File object
         */
        template<class T>
        File &operator<<(const std::vector<T> &data);

        /**
         * Write non-vector to file
         * \tparam T - variable type
         * \param info - {
         *                  val - variable non-vector to write
         *                  val_size - in case of array- array's size (else leave as default 1)
         *               }
         * \return this File object
         */
        template<class T>
        File &operator<<(const rw_s<T> &info);
    };

    template<class T>
    File &File::read(T *val, const size_t data_size) {
        if (!is_file_ready(0)) {
            return *this;
        }
        open(read_flags, FileAction::READ);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.read((char *) (val), sizeof(T) * data_size);

        update_rwm();
        return *this;
    }

    template<class T>
    File &File::write(const T *val, const size_t data_size) {
        if (!is_file_ready(0)) {
            return *this;
        }
        open(write_flags, FileAction::WRITE);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.write(reinterpret_cast<const char *>(val), sizeof(T) * data_size);

        update_rwm();
        return *this;
    }

    template<class T>
    File &File::read(std::vector<T> &val) {
        if (!is_file_ready(0)) {
            return *this;
        }
        open(read_flags, FileAction::READ);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.read(reinterpret_cast<char *>(val.data()), sizeof(T) * val.size());

        update_rwm();
        return *this;
    }

    template<typename T>
    File &File::write(const std::vector<T> &val) {
        if (!is_file_ready(0)) {
            return *this;
        }
        open(write_flags, FileAction::WRITE);
        std::lock_guard<std::mutex> guard(read_write_mutex);

        file_ptr.write(reinterpret_cast<const char *>(val.data()), sizeof(T) * val.size());

        update_rwm();
        return *this;
    }

    template<class T>
    File &File::operator>>(std::vector<T> &data) {
        return read(data);
    }

    template<class T>
    File &File::operator>>(const rw_s<T> &info) {
        return read(info.val, info.val_size);
    }

    template<class T>
    File &File::operator<<(const std::vector<T> &data) {
        return write(data);
    }

    template<class T>
    File &File::operator<<(const rw_s<T> &info) {
        return write(info.val, info.val_size);
    }
}

#endif //FILESAPI_FILE_H