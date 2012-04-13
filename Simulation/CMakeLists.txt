SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)



# PROJECT(Simulation)
ADD_EXECUTABLE(Simulation
	  main.cpp
	  Particle.cpp
	  Particle.h  
	  TimeManager.cpp
	  TimeManager.h
	  RigidBody.h
	  RigidBody.cpp
	  ./Integrators/IIntegratable.h
	  ./Integrators/Integrator.h
	  ./Integrators/Integrator.cpp
	  ./Integrators/SingleStepIntegrator.h
	  ./Integrators/SingleStepIntegrator.cpp
	  ./Integrators/CompositeIntegratable.h
	  ./Integrators/CompositeIntegratable.cpp
	  ./Integrators/Implementations/ExplicitEuler.h
	  ./Integrators/Implementations/ExplicitEuler.cpp
	  ./Integrators/Implementations/RungeKutta4.h
	  ./Integrators/Implementations/RungeKutta4.cpp
	  
	  
	  
	  ${VIS_FILES}                    
	  ${PROJECT_PATH}/Common/Config.h			  
	  ${PROJECT_PATH}/Common/StringTools.h			  
	  ${PROJECT_PATH}/Common/StringTools.cpp
	  ${PROJECT_PATH}/Common/timing.h			  	  
	  ${PROJECT_PATH}/Common/timing.cpp
	  CMakeLists.txt
)
ADD_DEPENDENCIES(Simulation ${SIMULATION_DEPENDENCIES})
TARGET_LINK_LIBRARIES(Simulation ${SIMULATION_LINK_LIBRARIES})
VIS_SOURCE_GROUPS()
COPY_ANTTWEAKBAR_DLL(Simulation)
