set(source 
./Log.h
./Log.cpp
../include/core.logging.h
)
source_group("" FILES ${source})
add_library(core.logging ${source} CMakeLists.txt)
target_link_libraries(core.logging core)