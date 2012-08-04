set(source 
 ./SOIL.h
 ./SOIL.c
 ./image_DXT.h
 ./image_DXT.c
 ./image_helper.h
 ./image_helper.c
 ./stb_image_aug.h
 ./stb_image_aug.c
 ./stbi_DDS_aug.h
 ./stbi_DDS_aug_c.h  
 ./test_SOIL.cpp
)
source_group("" FILES ${source})
find_package(opengl)
include_directories(${OPENGL_INCLUDE_DIR})
add_library(soil ${source} CMakeLists.txt)
target_link_libraries(soil ${OPENGL_LIBRARIES})
project_folder("externals" soil)


set(includeDirectories ${includeDirectories} ${CMAKE_CURRENT_SOURCE_DIR} INTERNAL)