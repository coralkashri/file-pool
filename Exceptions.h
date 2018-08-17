#ifndef FILESAPI_EXCEPTIONS_H
#define FILESAPI_EXCEPTIONS_H

#include <iostream>
#include <exception>


class FileOpenException: public std::runtime_error
{
    std::string _file_name;
    std::string what_message;

public:
    explicit FileOpenException(const std::string &file_name) : runtime_error("") {
        _file_name = file_name;
        what_message = "Can't open file '" + _file_name + "' exception.";
    }

    virtual const char* what() const throw()
    {
        return what_message.c_str();
    }
};

#endif //FILESAPI_EXCEPTIONS_H