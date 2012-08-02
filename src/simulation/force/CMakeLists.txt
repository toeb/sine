set(source
	./Force/Gravity.h
	./Force/Gravity.cpp
	./Force/DampedSpring.h
	./Force/DampedSpring.cpp 
	./Force/Force.h
	./Force/ForceAlgorithm.h	
	./Force/ForceAlgorithm.cpp
)
set(simulationSource ${simulationSource} ${source}  )
source_group("simulation\\force" FILES ${source})