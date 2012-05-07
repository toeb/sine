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
  ./Integrators/Implementations/IntegratorsManager.h
  ./Integrators/Implementations/IntegratorsManager.cpp
)
SET (simulationObjects_SRC
	./SimulationObjects/Particle.cpp
	./SimulationObjects/Particle.h   
	./SimulationObjects/RigidBody.h
	./SimulationObjects/RigidBody.cpp
	./SimulationObjects/Force.h
	./SimulationObjects/Box.h
	./SimulationObjects/Box.cpp
	./SimulationObjects/Sphere.h
	./SimulationObjects/Sphere.cpp
	./SimulationObjects/DampedSpring.h
	./SimulationObjects/DampedSpring.cpp
	./SimulationObjects/Connector.h
	./SimulationObjects/ParticleConnector.h
	./SimulationObjects/ParticleConnector.cpp
	./SimulationObjects/RigidBodyConnector.h
	./SimulationObjects/RigidBodyConnector.cpp
	./SimulationObjects/Body.h
	./SimulationObjects/Body.cpp
	./SimulationObjects/Gravity.h
	./SimulationObjects/Gravity.cpp
	./SimulationObjects/Joint.h
	./SimulationObjects/BallJoint.h
	./SimulationObjects/BallJoint.cpp
)
SET(simulation_SRC
	./SimulationRunner.h
	./SimulationRunner.cpp
	./CustomSimulation.h
	./CustomSimulation.cpp
	./Simulation.h
	./Simulation.cpp
	./ISimulationObject.h
	./TimeManager.cpp
	./TimeManager.h	
	./GlutSimulationRunner.h
	./GlutSimulationRunner.cpp
)

SET(visualisation_SRC
	  ${PROJECT_PATH}/Visualization/MiniGL.h
	  ${PROJECT_PATH}/Visualization/MiniGL.cpp
	  ${PROJECT_PATH}/Visualization/IRenderer.h
	${PROJECT_PATH}/Visualization/Renderer.h
	${PROJECT_PATH}/Visualization/Renderer.cpp
	${PROJECT_PATH}/Visualization/CompositeRenderer.h
	${PROJECT_PATH}/Visualization/CompositeRenderer.cpp
)	

source_group("integration" FILES ${integrators_SRC})
source_group("simulation" FILES ${simulation_SRC})
source_group("simulation objects" FILES ${simulationObjects_SRC})
source_group("visualization" FILES ${visualisation_SRC})

# PROJECT(Simulation)
ADD_EXECUTABLE(Simulation
	  main.cpp	  	  
	  ${integrators_SRC}
	  ${simulation_SRC}
	  ${simulationObjects_SRC}
	  ${visualisation_SRC}                    
	  ${PROJECT_PATH}/Common/Config.h			  
	  ${PROJECT_PATH}/Common/StringTools.h			  
	  ${PROJECT_PATH}/Common/StringTools.cpp
	  ${PROJECT_PATH}/Common/timing.h			  	  
	  ${PROJECT_PATH}/Common/timing.cpp
	  CMakeLists.txt
)
ADD_DEPENDENCIES(Simulation ${SIMULATION_DEPENDENCIES})
TARGET_LINK_LIBRARIES(Simulation ${SIMULATION_LINK_LIBRARIES})

COPY_ANTTWEAKBAR_DLL(Simulation)
