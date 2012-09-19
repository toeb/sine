SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

set(ClothSample_SRC 
	./CustomSimulation.h
	./CustomSimulation.cpp
	./main.cpp
)

source_group("src" FILES ${ClothSample_SRC})

add_executable(Sample_Cloth ${ClothSample_SRC})
add_dependencies(Sample_Cloth ${SIMULATION_DEPENDENCIES})
target_link_libraries(Sample_Cloth Simulation Visualization core ${SIMULATION_LINK_LIBRARIES})


COPY_ANTTWEAKBAR_DLL(Sample_Cloth)
