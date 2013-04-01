set(source ../include/core.utility.h )





set(utilitySource
StringTools.h
StringTools.cpp
SourceInfo.h
SourceInfo.cpp
Helpers.h
Helpers.cpp
Utilities.h
Utilities.cpp
Timer.h
Timer.cpp
ToString.h
ToString.cpp

CollectionTools.h
CollectionTools.cpp
)

source_group("" FILES ${utilitySource})
set(source ${source} ${utilitySource})

add_library(core.utility  ${source} CMakeLists.txt)
target_link_libraries(core.utility core core.reflection)

