set(source
./CMakeLists.txt

 ./TweakBarRenderer.h
 ./TweakBarRenderer.cpp
)

source_group("" FILES ${source})

add_library(visualization.opengl.renderer.tweakbar ${source})
target_link_libraries(visualization.opengl.renderer.tweakbar 
 visualization.opengl.renderer
 anttweakbar
 )