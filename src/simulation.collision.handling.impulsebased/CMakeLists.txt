set(source
  ./ContactJoint.h
  ./ContactJoint.cpp
  ./DynamicCollidable.h
  ./DynamicCollidable.cpp
  ./DynamicContact.h
  ./DynamicContact.cpp
  ./ImpulseBasedCollisionHandler.h
  ./ImpulseBasedCollisionHandler.cpp 
  
)
source_group("" FILES ${source})

add_library(simulation.colllision.detection.acceleration ${source} CMakeLists.txt)
target_link_libraries(simulation.colllision.detection.acceleration 
 simulation.collision.detection
 )
