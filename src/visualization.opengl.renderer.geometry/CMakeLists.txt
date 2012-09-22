set(source

./BoxRenderer.h
./BoxRenderer.cpp
./PlaneRenderer.h
./PlaneRenderer.cpp
./PointRenderer.h
./PointRenderer.cpp
./PolygonRenderer.h
./PolygonRenderer.cpp
./SphereRenderer.h
./SphereRenderer.cpp
./CoordinateSystemRenderer.h
./CoordinateSystemRenderer.cpp
./BoundingOctreeRenderer.h
./BoundingOctreeRenderer.cpp
)

source_group("" FILES ${source})

add_library(visualization.opengl.renderer.geometry ${source} ./CMakeLists.txt)
target_link_libraries(visualization.opengl.renderer.geometry 
 visualization.opengl.renderer
 simulation.geometry 
 )