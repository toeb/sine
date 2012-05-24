SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

SET (integrators_SRC
  ./Integrators/IIntegrable.h
  ./Integrators/Integrator.h
  ./Integrators/Integrator.cpp 
  ./Integrators/ISystemFunction.h
  ./Integrators/ISystemFunction.cpp
  ./Integrators/SingleStepIntegrator.h
  ./Integrators/SingleStepIntegrator.cpp
  ./Integrators/CompositeIntegratable.h
  ./Integrators/CompositeIntegratable.cpp)
  
SET (integratorImplementations_SRC
  ./Integrators/Implementations/ExplicitEuler.h
  ./Integrators/Implementations/ExplicitEuler.cpp
  ./Integrators/Implementations/ImplicitEuler.h
  ./Integrators/Implementations/ImplicitEuler.cpp
  ./Integrators/Implementations/RungeKutta4.h
  ./Integrators/Implementations/RungeKutta4.cpp
  ./Integrators/Implementations/RungeKuttaFehlberg45.h
  ./Integrators/Implementations/RungeKuttaFehlberg45.cpp)
 
 set(force_SRC
	./Force/Gravity.h
	./Force/Gravity.cpp
	./Force/DampedSpring.h
	./Force/DampedSpring.cpp 
	./Force/Force.h
	./Force/ForceAlgorithm.h	
	./Force/ForceAlgorithm.cpp
 )
 set(multibodydynamics_SRC
	./MultiBodyDynamics/Joint.h
	./MultiBodyDynamics/BallJoint.h
	./MultiBodyDynamics/BallJoint.cpp 
	./MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h
	./MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.cpp
 )

SET (dynamics_SRC
	./Dynamics/DynamicBodyModule.h
	./Dynamics/DynamicBodyModule.cpp
	./Dynamics/ConnectorModule.h
	./Dynamics/ConnectorModule.cpp
	./Dynamics/Particle.cpp
	./Dynamics/Particle.h   
	./Dynamics/RigidBody.h
	./Dynamics/RigidBody.cpp
	./Dynamics/Connector.h
	./Dynamics/Connector.cpp
	./Dynamics/ParticleConnector.h
	./Dynamics/ParticleConnector.cpp
	./Dynamics/RigidBodyConnector.h
	./Dynamics/RigidBodyConnector.cpp
	./Dynamics/DynamicBody.h
	./Dynamics/DynamicBody.cpp
)
set (bodyprimitives_SRC
	./Dynamics/BodyPrimitives/Box.h
	./Dynamics/BodyPrimitives/Box.cpp
	./Dynamics/BodyPrimitives/Sphere.h
	./Dynamics/BodyPrimitives/Sphere.cpp
)
set(runner_SRC
	./runner/SimulationRunner.h
	./runner/SimulationRunner.cpp
)
SET(simulation_SRC
	./Simulation.h
	./Simulation.cpp
	./ISimulationObject.h
	./SimulationBuilder.h
	./SimulationBuilder.cpp
	./ISimulationModule.h
	./SimulationModuleBase.h
	./SimulationModuleBase.cpp
	./DynamicsAlgorithm.h
	./DynamicsAlgorithm.cpp
	./CompositeSimulationModule.h
	./CompositeSimulationModule.cpp	
)

set(simulationCore_SRC
 ./Core/CompositeSimulationObject.h
 ./Core/CompositeSimulationObject.cpp
 )

SET(textile_SRC
./Textiles/TextileModel.h
./Textiles/TextileModel.cpp
./Textiles/TextileAlgorithm.h
./Textiles/TextileAlgorithm.cpp
)

SET(kinematics_SRC
./Kinematics/KinematicBody.h
./Kinematics/KinematicBody.cpp
)

SET(glutrunner_SRC
 ${PROJECT_PATH}/GlutRunner/GlutSimulationRunner.h
 ${PROJECT_PATH}/GlutRunner/GlutSimulationRunner.cpp
 ${PROJECT_PATH}/GlutRunner/GlutInputHandler.h
 ${PROJECT_PATH}/GlutRunner/GlutInputHandler.cpp
 ${PROJECT_PATH}/GlutRunner/GlutRendererManager.h
 ${PROJECT_PATH}/GlutRunner/GlutRendererManager.cpp 
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
	${PROJECT_PATH}/Visualization/InputHandler.h
	${PROJECT_PATH}/Visualization/InputHandler.cpp
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
	${PROJECT_PATH}/Visualization/Renderers/TextRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/TextRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/ConnectorRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/ConnectorRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/ConnectorVelocityRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/ConnectorVelocityRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/ConnectorForceRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/ConnectorForceRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/ParticleRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/ParticleRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/RigidBodyRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/RigidBodyRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/BoxRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/BoxRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/PointRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/PointRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/SphereRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/SphereRenderer.cpp	
	${PROJECT_PATH}/Visualization/Renderers/SpringRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/SpringRenderer.cpp	
	)
	
set(tweakbar_SRC
	${PROJECT_PATH}/Visualization/Renderers/TweakBar/TweakBarRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/TweakBar/TweakBarRenderer.h
)

set(userinterface_SRC
	${PROJECT_PATH}/Visualization/UserInterface/DelegateAction.h
	${PROJECT_PATH}/Visualization/UserInterface/DelegateAction.cpp
	${PROJECT_PATH}/Visualization/UserInterface/IValue.h
	${PROJECT_PATH}/Visualization/UserInterface/IValue.cpp
	${PROJECT_PATH}/Visualization/UserInterface/IAction.h
	${PROJECT_PATH}/Visualization/UserInterface/IAction.cpp
	${PROJECT_PATH}/Visualization/UserInterface/RealValue.h
	${PROJECT_PATH}/Visualization/UserInterface/RealValue.cpp
	${PROJECT_PATH}/Visualization/UserInterface/IDisplayable.h
	${PROJECT_PATH}/Visualization/UserInterface/IDisplayable.cpp
	${PROJECT_PATH}/Visualization/UserInterface/IUserInterface.h
	${PROJECT_PATH}/Visualization/UserInterface/IUserInterface.cpp
	${PROJECT_PATH}/Visualization/UserInterface/IComponent.h
	${PROJECT_PATH}/Visualization/UserInterface/IComponent.cpp
	${PROJECT_PATH}/Visualization/UserInterface/DelegateValue.h
	${PROJECT_PATH}/Visualization/UserInterface/DelegateValue.cpp
)
	
source_group("simulation\\integration" FILES ${integrators_SRC})
source_group("simulation\\integration\\implementations" FILES ${integratorImplementations_SRC})
source_group("simulation" FILES ${simulation_SRC})
source_group("simulation\\objects" FILES ${simulationObjects_SRC})
source_group("visualization" FILES ${visualisation_SRC})
source_group("visualization\\renderers" FILES ${renderers_SRC})
source_group("visualization\\userinterface" FILES ${userinterface_SRC})
source_group("visualization\\renderers\\tweakbar" FILES ${tweakbar_SRC})
source_group("simulation\\textiles" FILES ${textile_SRC})
source_group("simulation\\runner\\glut" FILES ${glutrunner_SRC})
source_group("simulation\\kinematics" FILES ${kinematics_SRC})
source_group("simulation\\runner" FILES ${runner_SRC})
source_group("simulation\\force" FILES ${force_SRC})
source_group("simulation\\dynamics" FILES ${dynamics_SRC})
source_group("simulation\\dynamics\\bodyprimitives" FILES ${bodyprimitives_SRC})
source_group("simulation\\multibodydynamics" FILES ${multibodydynamics_SRC})
source_group("simulation\\core" FILES ${simulationCore_SRC})

# PROJECT(Simulation)
add_library(Simulation 
${multibodydynamics_SRC}
${dynamics_SRC}
${force_SRC}
${runner_SRC}
	  ${integrators_SRC}
	  ${integratorImplementations_SRC}
	  ${simulation_SRC}
	  ${simulationObjects_SRC}
	  ${visualisation_SRC}         
	   ${renderers_SRC}
	   ${textile_SRC}
	   ${glutrunner_SRC}
	   ${kinematics_SRC}
	   ${bodyprimitives_SRC}
	   ${tweakbar_SRC}
	   ${simulationCore_SRC}
	   ${userinterface_SRC}
	  ${PROJECT_PATH}/Common/Config.h			  
	  ${PROJECT_PATH}/Common/StringTools.h			  
	  ${PROJECT_PATH}/Common/StringTools.cpp
	  ${PROJECT_PATH}/Common/timing.h			  	  
	  ${PROJECT_PATH}/Common/timing.cpp
	  CMakeLists.txt
)
#ADD_DEPENDENCIES(Simulation ${SIMULATION_DEPENDENCIES})
#TARGET_LINK_LIBRARIES(Simulation ${SIMULATION_LINK_LIBRARIES})

#COPY_ANTTWEAKBAR_DLL(Simulation)
