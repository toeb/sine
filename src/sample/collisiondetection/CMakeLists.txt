SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

set(CollisionExample_SRC
	./main.cpp
	./CustomSimulation.h
	./CustomSimulation.cpp
)

source_group("src" FILES ${CollisionExample_SRC})

add_executable(Sample_CollisionDetection ${CollisionExample_SRC})
add_dependencies(Sample_CollisionDetection ${SIMULATION_DEPENDENCIES})
target_link_libraries(Sample_CollisionDetection Simulation Visualization core ${SIMULATION_LINK_LIBRARIES})


COPY_ANTTWEAKBAR_DLL(Sample_CollisionDetection)
