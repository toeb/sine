set(source ../include/core.properties.h )




set(unifiedPropertyDefinitionSource

./Extensible.h
./Templated.h
./Simple.h
./Properties.h
./Members.h
)
source_group("" FILES ${unifiedPropertyDefinitionSource})
set(source ${source} ${unifiedPropertyDefinitionSource})



add_library(core.properties.h  ${source} CMakeLists.txt)

