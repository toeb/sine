
file(GLOB_RECURSE operationsSource 
    "operation/*.h"
    "operation/*.cpp"
)
source_group("operations" FILES ${operationsSource})

set(specialFunctionsSource
./specialfunctions/SpecialFunctions.h
./specialfunctions/SpecialFunctions.cpp
)

source_group("specialfunctions" FILES ${specialFunctionsSource})

set(source 
./CMakeLists.txt
./core.h
./core.cpp 
./constants.h
./operationcodes.h
./operations.h
./operators.h
../include/math.scalar.h
)
source_group("" FILES ${source})

add_library(math.scalar
${source}
${operationsSource}
${specialFunctionsSource}
)

target_link_libraries(math.scalar math.operation)