cmake_minimum_required(VERSION 2.6)
project(wuLabRecolor)
add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_LIBRARY_OUTOUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_RUNTIME_OUTOUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)

enable_testing()
add_test(NAME LabRecolorTest COMMAND Test)
