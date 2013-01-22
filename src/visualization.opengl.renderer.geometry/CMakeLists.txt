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
../include/visualization.opengl.renderer.geometry.h
)

source_group("" FILES ${source})
set(meshSource
 ./mesh/CubeMesh.h
 ./mesh/CubeMesh.cpp
 ./mesh/Mesh.h
 ./mesh/Mesh.cpp
 ./mesh/MeshRenderer.h
 ./mesh/MeshRenderer.cpp
 ./mesh/SphereMesh.h
 ./mesh/SphereMesh.cpp
 ./mesh/PlaneMesh.h
 ./mesh/PlaneMesh.cpp
 ./mesh/PlyMesh.h
 ./mesh/PlyMesh.cpp
 ./mesh/basic/BasicMeshRenderer.h
 ./mesh/basic/BasicMeshRenderer.cpp
 
)
source_group("mesh" FILES ${meshSource})
set(source ${source} ${meshSource})
add_library(visualization.opengl.renderer.geometry ${source} ./CMakeLists.txt)
target_link_libraries(visualization.opengl.renderer.geometry 
 visualization.opengl
 simulation.geometry 
 )