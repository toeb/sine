set(source
	./Gravity.h
	./Gravity.cpp
	./DampedSpring.h
	./DampedSpring.cpp 
	./Force.h
	./ForceModule.h	
	./ForceModule.cpp
	./ForceField.h	
	./ForceField.cpp
)

source_group("src" FILES ${source})
add_library(simulation.dynamics.force ${source})
target_link_libraries(simulation.dynamics.force simulation simulation.dynamics)
