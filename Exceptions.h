#ifndef FILESAPI_EXCEPTIONS_H
#define FILESAPI_EXCEPTIONS_H

#include <iostream>
#include <exception>


class FileOpenException: public std::exception
{
    std::string _file_name;

public:
    explicit FileOpenException(const std::string &file_name) {
        _file_name = file_name;
    }

    virtual const char* what() const throw()
    {
        return ("Can't open file '" + _file_name + "' exception.").c_str();
    }
};

#endif //FILESAPI_EXCEPTIONS_H