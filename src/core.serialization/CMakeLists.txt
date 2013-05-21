set(source 
 ../include/core.serialization.h
 CMakeLists.txt
 Serialization.h
 ISerializable.h
 ISerializable.cpp
Serializer.h
Deserializer.h
Serializer.cpp
Deserializer.cpp


)
source_group("" FILES ${source})
add_library(core.serialization ${source})
target_link_libraries(core.serialization core)