SET(collision_SRC
 ./Collision/Collision.h
 ./Collision/Collision.cpp
 ./Collision/Collidable.h
 ./Collision/Collidable.cpp
 ./Collision/Contact.h
 ./Collision/Contact.cpp
 ./Collision/ICollidable.h
 
)
source_group("simulation\\collision" FILES ${collision_SRC})
set(simulationSource ${simulationSource} ${collision_SRC})

set(collisionAcceleration_SRC 
./Collision/Detection/Acceleration/Octree.h
./Collision/Detection/Acceleration/Octree.cpp
)
source_group("simulation\\collision\\detection\\acceleration" FILES ${collisionAcceleration_SRC})
set(simulationSource ${simulationSource} ${collisionAcceleration_SRC})

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
set(simulationSource ${simulationSource} ${collisionDetection_SRC})

set(collisionHandling_SRC 
 ./Collision/Handling/ContactHandler.h
 ./Collision/Handling/ContactHandler.cpp
 ./Collision/Handling/ContactJoint.h
 ./Collision/Handling/ContactJoint.cpp
)
source_group("simulation\\collision\\handling" FILES ${collisionHandling_SRC})
set(simulationSource ${simulationSource} ${collisionHandling_SRC})

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
./Collision/Detection/CollisionTest/CollisionTestRepository.h
./Collision/Detection/CollisionTest/CollisionTestRepository.cpp	
./Collision/Detection/CollisionTest/ReverseCollisionTest.h
./Collision/Detection/CollisionTest/ReverseCollisionTest.cpp	
./Collision/Detection/CollisionTest/PlaneOctree.h
./Collision/Detection/CollisionTest/PlaneOctree.cpp	
./Collision/Detection/CollisionTest/SphereOctree.h
./Collision/Detection/CollisionTest/SphereOctree.cpp	
)
source_group("simulation\\collision\\detection\\collisiontest" FILES ${CollisionTests_SRC})
set(simulationSource ${simulationSource} ${CollisionTests_SRC})
