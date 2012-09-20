set(source
./ElementParser.h
./ElementParser.cpp
./CompositeChildParser.h
./CompositeChildParser.cpp
./CompositeElementParser.h
./CompositeElementParser.cpp
./NamedChildParser.h
./NamedChildParser.cpp
./ChildElementParser.h
./ChildElementParser.cpp
./SiblingElementParser.h
./SiblingElementParser.cpp
./NamedElementParser.h
./NamedElementParser.cpp
./xml.h
)

source_group("" FILES ${source})

add_library(utility.xml ${source} CMakeLists.txt)
target_link_libraries(utility.xml common tinyxml2)
