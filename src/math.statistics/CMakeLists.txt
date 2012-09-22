set(source
./Average.h
./Average.cpp
./AverageOverTime.h
./AverageOverTime.cpp
./AverageRate.h
./AverageRate.cpp
./IAverage.h
./IAverage.cpp
./Statistics.h
./Statistics.cpp
./core.h
)
source_group("" FILES ${source})

file(GLOB_RECURSE operationsSource 
    "operation/*.h"
    "operation/*.cpp"
)
source_group("operations" FILES ${operationsSource})

add_library(math.statistics ${source} ${operationsSource})
target_link_libraries(math.statistics math.matrix math.scalar)

