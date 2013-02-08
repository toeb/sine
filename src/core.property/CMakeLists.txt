set(source ../include/core.property.h )




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


add_library(core.property  ${source} CMakeLists.txt)


set_target_properties(core.property PROPERTIES LINKER_LANGUAGE CXX)