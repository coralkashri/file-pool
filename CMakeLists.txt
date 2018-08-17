cmake_minimum_required(VERSION 3.9)
project(filesAPI)

set(CMAKE_CXX_STANDARD 14)

add_executable(filesAPI CodeTests/FileTestVector.cpp src/Sources/FilesManager.cpp src/Headers/FilesManager.hpp src/Sources/File.cpp src/Headers/File.hpp src/Utilities/DesignText.cpp src/Utilities/DesignText.hpp CodeTests/FilesManagerTest.cpp CodeTests/FileTestNotVector.cpp CodeTests/FileTestOpertorsVectors.cpp CodeTests/FileTestOpertorsNotVectors.cpp CodeTests/ComplexDataStructureTest.cpp src/Utilities/Exceptions.hpp CodeTests/ExceptionsTester.cpp CodeTests/FilesManagerOperatorsTest.cpp CodeTests/README-Tests.cpp)