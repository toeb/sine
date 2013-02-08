set(source 
 ../include/core.serialization.h
 CMakeLists.txt
 Serialization.h
 ISerializable.h
 ISerializable.cpp


)

add_library(core.serialization ${source})
target_link_libraries(core.serialization core)