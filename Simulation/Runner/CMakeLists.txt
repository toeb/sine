set(runner_SRC
	./runner/SimulationRunner.h
	./runner/SimulationRunner.cpp
)
SET(glutrunner_SRC
 ${PROJECT_PATH}/GlutRunner/GlutSimulationRunner.h
 ${PROJECT_PATH}/GlutRunner/GlutSimulationRunner.cpp
 ${PROJECT_PATH}/GlutRunner/GlutInputHandler.h
 ${PROJECT_PATH}/GlutRunner/GlutInputHandler.cpp
 ${PROJECT_PATH}/GlutRunner/GlutRendererManager.h
 ${PROJECT_PATH}/GlutRunner/GlutRendererManager.cpp 
)
source_group("simulation\\runner\\glut" FILES ${glutrunner_SRC})
source_group("simulation\\runner" FILES ${runner_SRC})

set(simulationSource ${simulationSource} ${runner_SRC} ${glutrunner_SRC})