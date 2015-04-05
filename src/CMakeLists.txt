set(CMAKE_C_FLAGS "-Wall -g")
file(GLOB SRCS *.c *.h)
add_executable(lab-recolor ${SRCS})
