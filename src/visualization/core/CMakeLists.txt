set(source
 ./Viewport.h
 ./IRenderer.h
 ./RenderModule.h
 ./RenderModule.cpp  
 ./Color.h
 ./Color.cpp
 ./Material.h
 ./Material.cpp 
)
source_group("src" FILES ${source})
set(compositeSource
 ./composite/CompositeRenderer.h
 ./composite/CompositeRenderer.cpp
)
source_group("src\\composites" FILES ${compositeSource})

add_library(visualization ${source}  ${compositeSource} CMakeLists.txt)
target_link_libraries(visualization core math)
project_folder("visualization" visualization)



 
