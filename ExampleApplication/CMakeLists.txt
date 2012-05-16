SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

set(ExampleApplication_SRC 
	./CustomSimulation.h
	./CustomSimulation.cpp
	./main.cpp
)

source_group("src" FILES ${ExampleApplication_SRC})

add_executable(ExampleApplication ${ExampleApplication_SRC})
add_dependencies(ExampleApplication ${SIMULATION_DEPENDENCIES})
target_link_libraries(ExampleApplication Simulation ${SIMULATION_LINK_LIBRARIES})


COPY_ANTTWEAKBAR_DLL(ExampleApplication)
