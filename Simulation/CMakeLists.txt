SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

SET (integrators_SRC
  ./Integrators/IIntegrable.h
  ./Integrators/Integrator.h
  ./Integrators/Integrator.cpp 
  ./Integrators/SingleStepIntegrator.h
  ./Integrators/SingleStepIntegrator.cpp
  ./Integrators/CompositeIntegratable.h
  ./Integrators/CompositeIntegratable.cpp)
  
SET (integratorImplementations_SRC
  ./Integrators/Implementations/ExplicitEuler.h
  ./Integrators/Implementations/ExplicitEuler.cpp
  ./Integrators/Implementations/RungeKutta4.h
  ./Integrators/Implementations/RungeKutta4.cpp
  ./Integrators/Implementations/RungeKuttaFehlberg45.h
  ./Integrators/Implementations/RungeKuttaFehlberg45.cpp)
  
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
	./SimulationObjects/BallJoint.cpp)
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
	./RenderingSimulation.h
	./RenderingSimulation.cpp
	./SimulationBuilder.h
	./SimulationBuilder.cpp
)

SET(visualisation_SRC
	  ${PROJECT_PATH}/Visualization/MiniGL.h
	  ${PROJECT_PATH}/Visualization/MiniGL.cpp
	  ${PROJECT_PATH}/Visualization/IRenderer.h
	${PROJECT_PATH}/Visualization/RenderEngine.h
	${PROJECT_PATH}/Visualization/RenderEngine.cpp
	${PROJECT_PATH}/Visualization/CompositeRenderer.h
	${PROJECT_PATH}/Visualization/CompositeRenderer.cpp
	${PROJECT_PATH}/Visualization/RenderManager.h
	${PROJECT_PATH}/Visualization/RenderManager.cpp
)	
SET(renderers_SRC
	${PROJECT_PATH}/Visualization/Renderers/SimulationRunnerRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/SimulationRunnerRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/ForceRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/ForceRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/AccelerationRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/AccelerationRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/VelocityRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/VelocityRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/LightRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/LightRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/CameraRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/CameraRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/CoordinateSystemRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/CoordinateSystemRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/TweakBarRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/TweakBarRenderer.h
	)
	
source_group("integration" FILES ${integrators_SRC})
source_group("integration\\implementations" FILES ${integratorImplementations_SRC})
source_group("simulation" FILES ${simulation_SRC})
source_group("simulation\\objects" FILES ${simulationObjects_SRC})
source_group("visualization" FILES ${visualisation_SRC})
source_group("visualization\\renderers" FILES ${renderers_SRC})

# PROJECT(Simulation)
ADD_EXECUTABLE(Simulation
	  main.cpp	  	  
	  ${integrators_SRC}
	  ${integratorImplementations_SRC}
	  ${simulation_SRC}
	  ${simulationObjects_SRC}
	  ${visualisation_SRC}         
	   ${renderers_SRC}
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
