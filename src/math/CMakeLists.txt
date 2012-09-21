

set(source
	./definitions.h
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

add_library(math ${source} CMakeLists.txt ../config.h)
target_link_libraries(math core 
 math.linearalgebra
 math.linearalgebra.dslib
 math.linearalgebra.ibds
 math.linearalgebra.eigen
 
)

