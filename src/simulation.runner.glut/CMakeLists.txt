
set(source 
 ./GlutSimulationRunner.h
 ./GlutSimulationRunner.cpp
 ./GlutRenderModule.h
 ./GlutRenderModule.cpp
 ./GlutInputHandler.h
 ./GlutInputHandler.cpp
 
)

source_group("src" FILES ${source})
add_library(simulation.runner.glut ${source} CMakeLists.txt)
target_link_libraries(simulation.runner.glut simulation.runner visualization.opengl)
