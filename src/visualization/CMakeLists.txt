set(source
 ./Viewport.h
 ./Viewport.cpp
 ./PerspectiveViewport.h
 ./PerspectiveViewport.cpp
 ./Renderer.h
 ./Renderer.cpp
 ./RenderSet.h
 ./RenderSet.cpp  
 ./Color.h
 ./Color.cpp
 ./Material.h
 ./Material.cpp 
 ./Texture.h
 ./Texture.cpp 
 ./ViewportController.h
 ./ViewportController.cpp 
 ./SceneObject.h
 ./SceneObject.cpp 
 ./Camera.h
 ./Camera.cpp 
 
)
source_group("" FILES ${source})

add_library(visualization ${source}  CMakeLists.txt)
target_link_libraries(visualization core.hub math lodepng)



 
