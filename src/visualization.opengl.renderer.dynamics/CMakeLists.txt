set(source
./CMakeLists.txt
./CollisionRenderer.h
./CollisionRenderer.cpp
./ConnectorForceRenderer.h
./ConnectorForceRenderer.cpp
./ConnectorRenderer.h
./ConnectorRenderer.cpp
./ConnectorVelocityRenderer.h
./ConnectorVelocityRenderer.cpp
./ParticleRenderer.h
./ParticleRenderer.cpp
./SpringRenderer.h
./SpringRenderer.cpp

)

source_group("" FILES ${source})

add_library(visualization.opengl.renderer.dynamics ${source})
target_link_libraries(visualization.opengl.renderer.dynamics 
 visualization.opengl.renderer
 simulation.dynamics
 simulation.dynamics.force
 simulation.collision
 simulation.collision.detection
 )