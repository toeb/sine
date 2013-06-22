set(source
 JsonSerializer.h
 JsonSerializer.cpp
 JsonDeserializer.h
 JsonDeserializer.cpp
 JsonValueConverter.h
 JsonValueConverter.cpp
 PrimitiveJsonValueConverter.h
 PrimitiveJsonValueConverter.cpp
 VectorJsonValueConverter.h
 VectorJsonValueConverter.cpp
 JsonDeserializer.h
 JsonDeserializer.cpp
 ObjectJsonValueConverter.h
 ObjectJsonValueConverter.cpp
 TypedJsonValueConverter.h
 ../include/utility.serialization.json.h
)
source_group("" FILES ${source})
add_library(utility.serialization.json ${source})
target_link_libraries(utility.serialization.json core.serialization lib_json)
