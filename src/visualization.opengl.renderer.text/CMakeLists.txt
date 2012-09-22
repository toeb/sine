set(source
./CMakeLists.txt
./TextRenderer.h
./TextRenderer.cpp
)

source_group("" FILES ${source})

add_library(visualization.opengl.renderer.text ${source})
target_link_libraries(visualization.opengl.renderer.text  
 visualization.opengl.renderer
 
 )