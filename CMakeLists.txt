cmake_minimum_required(VERSION 2.8)
project(Test)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_path(EIGEN3_INCLUDE_DIR NAMES signature_of_eigen3_matrix_library
    PATHS
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    PATH_SUFFIXES eigen3 eigen
)
