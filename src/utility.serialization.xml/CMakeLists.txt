set(source
 XmlSerializer.h
 XmlSerializer.cpp
 XmlDeserializer.h
 XmlDeserializer.cpp
 
)
source_group("" FILES ${source})
add_library(utility.serialization.xml ${source})
target_link_libraries(utility.serialization.xml utility.xml)
