set(source
./ElementParser.h
./CompositeChildParser.h
./CompositeElementParser.h
./NamedChildParser.h
./ChildElementParser.h
./SiblingElementParser.h
./NamedElementParser.h
)

source_group("" FILES ${source})

add_library(xml ${source} CMakeLists.txt)
target_link_libraries(xml common tinyxml2)
project_folder("utility" xml)
