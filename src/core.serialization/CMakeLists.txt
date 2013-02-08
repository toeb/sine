set(source 
 ../include/core.serialization.h
 CMakeLists.txt
 Serialization.h
 ISerialization.h
 ISerialization.cpp


)

add_library(core.serialization ${source})
target_link_libraries(core.serialization core)