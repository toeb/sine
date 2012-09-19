SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

set(MultibodySample_SRC
	./main.cpp
)

source_group("src" FILES ${MultibodySample_SRC})

add_executable(Sample_Multibody ${MultibodySample_SRC})
add_dependencies(Sample_Multibody ${SIMULATION_DEPENDENCIES})
target_link_libraries(Sample_Multibody Simulation Visualization core ${SIMULATION_LINK_LIBRARIES})


COPY_ANTTWEAKBAR_DLL(Sample_Multibody)
