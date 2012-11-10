set(source lodepng.h lodepng.cpp)
source_group("" FILES ${source})
add_library(lodepng ${source} CMakeLists.txt)
project_folder(${dslibExternalsProjectFolder} lodepng)
