project(MainLib)
set(CMAKE_C_FLAGS "-Wall -g")
add_library(LabRecolor lab_recolor.c lab_recolor.h)
add_executable(lab-recolor main.c)

find_package(ImageMagick COMPONENTS MagickWand REQUIRED)
if (ImageMagick_FOUND)
  include_directories(LabRecolor ${ImageMagick_INCLUDE_DIRS})
  target_link_libraries(LabRecolor m ${ImageMagick_LIBRARIES})
endif (ImageMagick_FOUND)

target_link_libraries(lab-recolor LabRecolor)
