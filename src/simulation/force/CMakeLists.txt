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
add_library(force ${source})
project_folder("simulation/modules" force)
target_link_libraries(force core dynamics)
