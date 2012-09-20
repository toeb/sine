set(source
  ./Octree.h
  ./Octree.cpp
  
  
)
source_group("" FILES ${source})

add_library(simulation.collision.detection.acceleration ${source} CMakeLists.txt)
target_link_libraries(simulation.collision.detection.acceleration 
 simulation.collision.detection
 simulation.geometry 
 )
