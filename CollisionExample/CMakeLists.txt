SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

set(CollisionExample_SRC
	./main.cpp
	./CustomSimulation.h
	./CustomSimulation.cpp
)

source_group("src" FILES ${CollisionExample_SRC})

add_executable(CollisionExample ${CollisionExample_SRC})
add_dependencies(CollisionExample ${SIMULATION_DEPENDENCIES})
target_link_libraries(CollisionExample Simulation ${SIMULATION_LINK_LIBRARIES})


COPY_ANTTWEAKBAR_DLL(CollisionExample)
