
set(source 
 ./GlutSimulationRunner.h
 ./GlutSimulationRunner.cpp
 ./GlutRenderModule.h
 ./GlutRenderModule.cpp
 ./GlutInputHandler.h
 ./GlutInputHandler.cpp
 
)

source_group("src" FILES ${source})
add_library(glutrunner ${source} CMakeLists.txt)
target_link_libraries(glutrunner runner opengl)
project_folder("runners" glutrunner)
