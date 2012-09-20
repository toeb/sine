set(source
 ./Viewport.h
 ./IRenderer.h
 ./RenderModule.h
 ./RenderModule.cpp  
 ./Color.h
 ./Color.cpp
 ./Material.h
 ./Material.cpp 
 ./Image.h
 ./Image.cpp 
 ./Pixel.h
 ./Pixel.cpp 
 ./Texture.h
 ./Texture.cpp 
 ./ViewportController.h
 ./ViewportController.cpp 
 ./SceneObject.h
 ./SceneObject.cpp 
 ./Camera.h
 ./Camera.cpp 
 
)
source_group("src" FILES ${source})
set(compositeSource
 ./composite/CompositeRenderer.h
 ./composite/CompositeRenderer.cpp
)
source_group("src\\composites" FILES ${compositeSource})

add_library(visualization ${source}  ${compositeSource} CMakeLists.txt)
target_link_libraries(visualization simulation math lodepng)



 
