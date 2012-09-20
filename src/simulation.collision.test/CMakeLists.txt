set(source 
./CollisionTest.h
./CollisionTest.cpp
./CollisionTestRepository.h
./CollisionTestRepository.cpp
./OctreeOctree.h
./OctreeOctree.cpp
./PlaneOctree.h
./PlaneOctree.cpp
./ReverseCollisionTest.h
./ReverseCollisionTest.cpp
./SeparatingAxes.h
./SeparatingAxes.cpp
./SphereOctree.h
./SphereOctree.cpp
./SpherePlane.h
./SpherePlane.cpp
./SphereSphere.h
./SphereSphere.cpp
)
source_group("" FILES ${source} CMakeLists.txt)
add_library(simulation.collision.test ${source})
target_link_libraries(simulation.collision.test
simulation.collision
simulation.geometry
)