set(source
 JsonSerializer.h
 JsonSerializer.cpp
 JsonDeserializer.h
 JsonDeserializer.cpp
 ../include/utility.serialization.json.h
)
source_group("" FILES ${source})
add_library(utility.serialization.json ${source})
target_link_libraries(utility.serialization.json lib_json)
