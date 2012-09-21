

set(source
	./definitions.h
	./ScalarOperations.h
	./ScalarConstants.h
	./CDMath.cpp
	./CDMath.h
	./MathDefs.h
	./SimMath.cpp
	./SimMath.h
	./IAverage.h
	./IAverage.cpp
	./Average.h
	./Average.cpp
	./AverageRate.h
	./AverageRate.cpp
	./AverageOverTime.h
	./AverageOverTime.cpp
	./Statistics.h
	./Statistics.cpp
../config.h
	
)
source_group("" FILES ${source})


file(GLOB_RECURSE operationsSource 
    "operations/*.h"
    "operations/*.cpp"
)
source_group("operations" FILES ${operationsSource})

add_library(math ${source} ${operationsSource} CMakeLists.txt ../config.h)
target_link_libraries(math core 
 math.linearalgebra
 math.linearalgebra.dslib
 math.linearalgebra.ibds
 math.linearalgebra.eigen
 
)

