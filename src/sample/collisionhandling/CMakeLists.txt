
set(CollisionExample_SRC
	./main.cpp
	./CustomSimulation.h
	./CustomSimulation.cpp
)

source_group("src" FILES ${CollisionExample_SRC})

add_executable(Sample_CollisionHandling ${CollisionExample_SRC})
add_dependencies(Sample_CollisionHandling ${SIMULATION_DEPENDENCIES})
target_link_libraries(Sample_CollisionHandling Simulation Visualization core ${SIMULATION_LINK_LIBRARIES})


COPY_ANTTWEAKBAR_DLL(Sample_CollisionHandling)
