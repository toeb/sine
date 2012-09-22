
file(GLOB_RECURSE operationsSource 
    "operation/*.h"
    "operation/*.cpp"
)
source_group("operations" FILES ${operationsSource})

set(source 
./CMakeLists.txt
./core.h
./core.cpp 
./constants.h
./operationcodes.h
./operations.h
./operators.h
)
source_group("" FILES ${source})

add_library(math.scalar
${source}
${operationsSource})

target_link_libraries(math.scalar math.operation)