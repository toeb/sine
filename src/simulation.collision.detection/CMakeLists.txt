set(source
  ./CollisionDetector.h
  ./CollisionDetector.cpp
  ./CompositeCollisionDetector.h
  ./CompositeCollisionDetector.cpp
  
)
source_group("" FILES ${source})

add_library(simulation.collision.detection ${source} CMakeLists.txt)
target_link_libraries(simulation.collision.detection 
 simulation.collision
 simulation.collision.test)