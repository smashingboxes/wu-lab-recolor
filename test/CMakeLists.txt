add_executable(Test test.c)
include_directories(${MainLib_SOURCE_DIR})
target_link_libraries(Test LabRecolor)
