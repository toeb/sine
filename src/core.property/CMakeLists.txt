set(source ../include/core.properties.h )




set(unifiedPropertyDefinitionSource

./Extensible.h
./Templated.h
./Simple.h
./Properties.h
./Properties.cpp
./Members.h
)
source_group("" FILES ${unifiedPropertyDefinitionSource})
set(source ${source} ${unifiedPropertyDefinitionSource})


add_library(core.properties  ${source} CMakeLists.txt)


set_target_properties(core.properties PROPERTIES LINKER_LANGUAGE CXX)