set(source 
	../include/core.serialization.h
	CMakeLists.txt
	Serialization.h
	Serialization.cpp
	SerializationContext.h
	SerializationContext.cpp
	ISerializable.h
	ISerializable.cpp
	Serializer.h
	Deserializer.h
	Serializer.cpp
	Deserializer.cpp
	DeserializationContext.h
	DeserializationContext.cpp
	
	
)
source_group("" FILES ${source})
add_library(core.serialization ${source})
target_link_libraries(core.serialization core core.task core.reflection utility.reader)