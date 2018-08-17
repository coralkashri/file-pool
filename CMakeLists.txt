cmake_minimum_required(VERSION 3.9)
project(filesAPI)

set(CMAKE_CXX_STANDARD 14)

add_executable(filesAPI CodeTests/FileTestVector.cpp FilesManager.cpp FilesManager.h File.cpp File.h DesignText.cpp DesignText.h CodeTests/FilesManagerTest.cpp CodeTests/FileTestNotVector.cpp CodeTests/FileTestOpertorsVectors.cpp CodeTests/FileTestOpertorsNotVectors.cpp CodeTests/ComplexDataStructureTest.cpp Exceptions.h CodeTests/ExceptionsTester.cpp CodeTests/FilesManagerOperatorsTest.cpp)