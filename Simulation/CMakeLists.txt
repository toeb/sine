SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)


set(simulationSource 
	./SimulationBuilder.h
	./SimulationBuilder.cpp
	./DynamicsAlgorithm.h
	./DynamicsAlgorithm.cpp	
)
set(commonSource 
${PROJECT_PATH}/Common/Config.h			  
${PROJECT_PATH}/Common/StringTools.h			  
${PROJECT_PATH}/Common/StringTools.cpp
${PROJECT_PATH}/Common/timing.h			  	  
${PROJECT_PATH}/Common/timing.cpp
)
source_group("simulation" FILES ${simulationSource})
source_group("common" FILES ${commonSource})

include(Collision/CMakeLists.txt)
include(Core/CMakeLists.txt)
include(Dynamics/CMakeLists.txt)
include(Force/CMakeLists.txt)
include(Geometry/CMakeLists.txt)
include(Integration/CMakeLists.txt)
include(Kinematics/CMakeLists.txt)
include(MultiBodyDynamics/CMakeLists.txt)
include(Runner/CMakeLists.txt)
include(Textiles/CMakeLists.txt)

# PROJECT(Simulation)
add_library(Simulation ${simulationSource} ${commonSource} CMakeLists.txt)

