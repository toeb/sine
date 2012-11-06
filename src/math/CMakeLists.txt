

set(source
	./CDMath.cpp
	./CDMath.h
	./MathDefs.h
	./SimMath.cpp
	./SimMath.h
	./core.h
../config.h
Interval.h
Interval.cpp
	./CMakeLists.txt 
)
source_group("" FILES ${source})


add_library(math ${source}  )
target_link_libraries(math 
core 
 math.operation
 math.scalar
 math.matrix
 math.matrix.dslib
 math.matrix.eigen
 math.statistics
 
)

