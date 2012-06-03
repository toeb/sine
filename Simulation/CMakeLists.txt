SET(SIMULATION_LINK_LIBRARIES Math freeglut opengl32.lib glu32.lib ${ANTTWEAKBAR_LIBS})
SET (SIMULATION_DEPENDENCIES Math freeglut)

set(collisionAcceleration_SRC 
./Collision/Detection/Acceleration/Octree.h
./Collision/Detection/Acceleration/Octree.cpp
)


source_group("simulation\\collision\\detection\\acceleration" FILES ${collisionAcceleration_SRC})

SET(collision_SRC
 ./Collision/Collision.h
 ./Collision/Collision.cpp
 ./Collision/Collidable.h
 ./Collision/Collidable.cpp
)
source_group("simulation\\collision" FILES ${collision_SRC})

set(collisionDetection_SRC 
 ./Collision/Detection/CollisionDetector.h
 ./Collision/Detection/CollisionDetector.cpp
 ./Collision/Detection/CompositeCollisionDetector.h
 ./Collision/Detection/CompositeCollisionDetector.cpp
 ./Collision/Detection/SphereCollisionDetector.h
 ./Collision/Detection/SphereCollisionDetector.cpp
 ./Collision/Detection/OctreeCollisionDetector.h
 ./Collision/Detection/OctreeCollisionDetector.cpp 
)
source_group("simulation\\collision\\detection" FILES ${collisionDetection_SRC})

set(geometry_SRC
 ./Geometry/Geometry.h
 ./Geometry/Geometry.cpp
 ./Geometry/CoordinateSystem.h
 ./Geometry/CoordinateSystem.cpp
 ./Geometry/Plane.h
 ./Geometry/Plane.cpp
 ./Geometry/Interval.h
 ./Geometry/Interval.cpp
 ./Geometry/Axis.h
 ./Geometry/Axis.cpp
)
source_group("simulation\\geometry" FILES ${geometry_SRC})

set(boundingVolumes_SRC
 ./Geometry/BoundingVolumes/BoundingSphere.h
 ./Geometry/BoundingVolumes/BoundingSphere.cpp
 ./Geometry/BoundingVolumes/BoundingVolume.h
 ./Geometry/BoundingVolumes/BoundingVolume.cpp
 ./Geometry/BoundingVolumes/BoundingBox.h
 ./Geometry/BoundingVolumes/BoundingBox.cpp 
)
source_group("simulation\\geometry\\boundingvolumes" FILES ${boundingVolumes_SRC})


set(polygon_SRC
 ./Geometry/Polygon/Polygon.h
 ./Geometry/Polygon/Polygon.cpp
 ./Geometry/Polygon/Vertex.h
 ./Geometry/Polygon/Vertex.cpp
 ./Geometry/Polygon/HalfEdge.h
 ./Geometry/Polygon/HalfEdge.cpp
 ./Geometry/Polygon/Edge.h
 ./Geometry/Polygon/Edge.cpp
 ./Geometry/Polygon/Face.h
 ./Geometry/Polygon/Face.cpp
 ./Geometry/Polygon/Element.h
 ./Geometry/Polygon/Element.cpp
)
source_group("simulation\\geometry\\polygon" FILES ${polygon_SRC})

set(CollisionTests_SRC
./Collision/Detection/CollisionTest/SphereSphere.h
./Collision/Detection/CollisionTest/SphereSphere.cpp
./Collision/Detection/CollisionTest/SpherePlane.h
./Collision/Detection/CollisionTest/SpherePlane.cpp
./Collision/Detection/CollisionTest/CollisionTest.h
./Collision/Detection/CollisionTest/CollisionTest.cpp
./Collision/Detection/CollisionTest/SeparatingAxes.h
./Collision/Detection/CollisionTest/SeparatingAxes.cpp
./Collision/Detection/CollisionTest/OctreeOctree.h
./Collision/Detection/CollisionTest/OctreeOctree.cpp
./Collision/Detection/CollisionTest/CollisionTestFactory.h
./Collision/Detection/CollisionTest/CollisionTestFactory.cpp	
./Collision/Detection/CollisionTest/ReverseCollisionTest.h
./Collision/Detection/CollisionTest/ReverseCollisionTest.cpp	
./Collision/Detection/CollisionTest/PlaneOctree.h
./Collision/Detection/CollisionTest/PlaneOctree.cpp	
./Collision/Detection/CollisionTest/SphereOctree.h
./Collision/Detection/CollisionTest/SphereOctree.cpp	
)
source_group("simulation\\collision\\detection\\collisiontest" FILES ${CollisionTests_SRC})


set(geometryPrimitives_SRC
 ./Geometry/Primitives/Cylinder.h
 ./Geometry/Primitives/Cylinder.cpp
 ./Geometry/Primitives/Hexahedron.h
 ./Geometry/Primitives/Hexahedron.cpp
 ./Geometry/Primitives/Sphere.h
 ./Geometry/Primitives/Sphere.cpp
 ./Geometry/Primitives/Rectangle.h
 ./Geometry/Primitives/Rectangle.cpp
 ./Geometry/Primitives/Pyramid.h
 ./Geometry/Primitives/Pyramid.cpp
 ./Geometry/Primitives/Triangle.h
 ./Geometry/Primitives/Triangle.cpp
)
source_group("simulation\\geometry\\primitives" FILES ${geometryPrimitives_SRC})
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
	./SimulationBuilder.h
	./SimulationBuilder.cpp
	./DynamicsAlgorithm.h
	./DynamicsAlgorithm.cpp
)
set(implicitGeometry_SRC
	./Geometry/Implicit/ImplicitSurface.h
	./Geometry/Implicit/ImplicitSurface.cpp
)
source_group("simulation\\geometry\\implicit" FILES ${implicitGeometry_SRC})
set(simulationCore_SRC
	./Core/CompositeSimulationObject.h
	./Core/CompositeSimulationObject.cpp
	./Core/ISimulationModule.h
	./Core/Simulation.h
	./Core/Simulation.cpp
	./Core/CompositeSimulationModule.h
	./Core/CompositeSimulationModule.cpp	
	./Core/SimulationModuleBase.h
	./Core/SimulationModuleBase.cpp
	./Core/ISimulationObject.h
	./Core/ISimulationObject.cpp
	./Core/IUpdateable.h
	./Core/IUpdateable.cpp
	./Core/UpdateablesModule.h
	./Core/UpdateablesModule.cpp	
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
	${PROJECT_PATH}/Visualization/Renderers/PolygonRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/PolygonRenderer.cpp
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
	${PROJECT_PATH}/Visualization/Renderers/BoxRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/BoxRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/PointRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/PointRenderer.cpp
	${PROJECT_PATH}/Visualization/Renderers/SphereRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/SphereRenderer.cpp	
	${PROJECT_PATH}/Visualization/Renderers/SpringRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/SpringRenderer.cpp	
	${PROJECT_PATH}/Visualization/Renderers/CollisionRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/CollisionRenderer.cpp	
	${PROJECT_PATH}/Visualization/Renderers/BoundingSphereHierarchyRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/BoundingSphereHierarchyRenderer.cpp	
	${PROJECT_PATH}/Visualization/Renderers/PlaneRenderer.h
	${PROJECT_PATH}/Visualization/Renderers/PlaneRenderer.cpp	
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
	${PROJECT_PATH}/Visualization/UserInterface/Vector3DValue.h
	${PROJECT_PATH}/Visualization/UserInterface/Vector3DValue.cpp
	
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
${boundingVolumes_SRC}
${multibodydynamics_SRC}
${polygon_SRC}
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
${collision_SRC} 
${collisionDetection_SRC} 
${geometry_SRC} 
${collisionAcceleration_SRC}
${geometryPrimitives_SRC}
${CollisionTests_SRC}
${implicitGeometry_SRC}
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
