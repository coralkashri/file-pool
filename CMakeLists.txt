cmake_minimum_required(VERSION 3.9)
project(filesAPI)

set(CMAKE_CXX_STANDARD 11)

add_executable(filesAPI main.cpp FilesManager.cpp FilesManager.h File.cpp File.h)