cmake_minimum_required(VERSION 3.9)
project(filesAPI)

set(CMAKE_CXX_STANDARD 14)

add_executable(filesAPI CodeTests/FileTestVector.cpp src/FilesManager.cpp src/FilesManager.hpp src/File.cpp src/File.hpp src/utilities/DesignText.cpp src/utilities/DesignText.hpp CodeTests/FilesManagerTest.cpp CodeTests/FileTestNotVector.cpp CodeTests/FileTestOpertorsVectors.cpp CodeTests/FileTestOpertorsNotVectors.cpp CodeTests/ComplexDataStructureTest.cpp src/utilities/Exceptions.hpp CodeTests/ExceptionsTester.cpp CodeTests/FilesManagerOperatorsTest.cpp CodeTests/README-Tests.cpp)