
set(implicitGeometry_SRC
	./implicit/ImplicitSurface.h
	./implicit/ImplicitSurface.cpp
)
source_group("implicit" FILES ${implicitGeometry_SRC})
set(source ${source} ${implicitGeometry_SRC}  )

set(geometry_SRC
 ./Geometry.h
 ./Geometry.cpp
 ./Plane.h
 ./Plane.cpp
 ./Interval.h
 ./Interval.cpp
 ./Axis.h
 ./Axis.cpp
 ../include/simulation.geometry.h
)

set(mesh_SRC
 ./mesh/Mesh.h
 ./mesh/Mesh.cpp
 ./mesh/MeshOperations.h
 ./mesh/MeshOperations.cpp
 
)
source_group("mesh" FILES ${mesh_SRC})
set(meshBasic_SRC
./mesh/basic/BasicMesh.h
./mesh/basic/BasicMesh.cpp
./mesh/basic/BasicMeshBuilder.h
./mesh/basic/BasicMeshBuilder.cpp
)
source_group("mesh\\basic" FILES ${meshBasic_SRC})


source_group("" FILES ${geometry_SRC})
set(source ${source} ${geometry_SRC}  )

set(boundingVolumes_SRC
 ./boundingVolumes/BoundingSphere.h
 ./boundingVolumes/BoundingSphere.cpp
 ./boundingVolumes/BoundingVolume.h
 ./boundingVolumes/BoundingVolume.cpp
 ./boundingVolumes/BoundingBox.h
 ./boundingVolumes/BoundingBox.cpp 
 ./boundingVolumes/BoundingOctree.h
 ./boundingVolumes/BoundingOctree.cpp 
)
source_group("boundingvolumes" FILES ${boundingVolumes_SRC})
set(source ${source} ${boundingVolumes_SRC}  )

set(geometryPrimitives_SRC
 ./primitives/Cylinder.h
 ./primitives/Cylinder.cpp
 ./primitives/Hexahedron.h
 ./primitives/Hexahedron.cpp
 ./primitives/Sphere.h
 ./primitives/Sphere.cpp
 ./primitives/Rectangle.h
 ./primitives/Rectangle.cpp
 ./primitives/Pyramid.h
 ./primitives/Pyramid.cpp
 ./primitives/Triangle.h
 ./primitives/Triangle.cpp
)

source_group("primitives" FILES ${geometryPrimitives_SRC})
set(source ${source} ${geometryPrimitives_SRC}  )

set(polygon_SRC
 ./polygon/Polygon.h
 ./polygon/Polygon.cpp
 ./polygon/Vertex.h
 ./polygon/Vertex.cpp
 ./polygon/HalfEdge.h
 ./polygon/HalfEdge.cpp
 ./polygon/Edge.h
 ./polygon/Edge.cpp
 ./polygon/Face.h
 ./polygon/Face.cpp
 ./polygon/Element.h
 ./polygon/Element.cpp
)
source_group("polygon" FILES ${polygon_SRC})
set(source ${source} ${polygon_SRC} ${meshBasic_SRC} ${mesh_SRC})


add_library(simulation.geometry ${source} CMakeLists.txt)
target_link_libraries(simulation.geometry simulation math)


