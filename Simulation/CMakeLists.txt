SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

SET (integrators_SRC
  ./Integrators/IIntegrable.h
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
  ./Integrators/Implementations/RungeKuttaFehlberg45.h
  ./Integrators/Implementations/RungeKuttaFehlberg45.cpp
)
SET(simulation_SRC
	./Simulation.h
	./Simulation.cpp
	./ISimulationObject.h
	Particle.cpp
	Particle.h   
	RigidBody.h
	RigidBody.cpp
	TimeManager.cpp
	  TimeManager.h
	Force.h
	Box.h
	Box.cpp
	DampedSpring.h
	DampedSpring.cpp
	Connector.h
	ParticleConnector.h
	ParticleConnector.cpp
	RigidBodyConnector.h
	RigidBodyConnector.cpp
	Body.h
	Body.cpp
	Gravity.h
	Gravity.cpp
)
source_group("integration" FILES ${integrators_SRC})
source_group("simulation" FILES ${simulation_SRC})

# PROJECT(Simulation)
ADD_EXECUTABLE(Simulation
	  main.cpp	  	  
	  ${integrators_SRC}
	  ${simulation_SRC}
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
