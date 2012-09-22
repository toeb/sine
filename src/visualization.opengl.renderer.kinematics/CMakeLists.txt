set(source
./CMakeLists.txt
)

source_group("" FILES ${source})

add_library(visualization.opengl.renderer.kinematics ${source})
target_link_libraries(visualization.opengl.renderer.kinematics 
 visualization.opengl.renderer
 simulation.kinematics
 
 )