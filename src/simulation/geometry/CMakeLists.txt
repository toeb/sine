
set(implicitGeometry_SRC
	./Geometry/Implicit/ImplicitSurface.h
	./Geometry/Implicit/ImplicitSurface.cpp
)
source_group("simulation\\geometry\\implicit" FILES ${implicitGeometry_SRC})
set(simulationSource ${simulationSource} ${implicitGeometry_SRC}  )

set(geometry_SRC
 ./Geometry/Geometry.h
 ./Geometry/Geometry.cpp
 ./Geometry/Plane.h
 ./Geometry/Plane.cpp
 ./Geometry/Interval.h
 ./Geometry/Interval.cpp
 ./Geometry/Axis.h
 ./Geometry/Axis.cpp
)

set(mesh_SRC
 ./Geometry/Mesh/Mesh.h
 ./Geometry/Mesh/Mesh.cpp
 
)
source_group("simulation\\geometry\\mesh" FILES ${mesh_SRC})
set(meshPly_SRC
./Geometry/Mesh/Ply/PlyMesh.h
./Geometry/Mesh/Ply/PlyMesh.cpp
./Geometry/Mesh/Ply/rply.h
./Geometry/Mesh/Ply/rply.c
)
source_group("simulation\\geometry\\mesh\\ply" FILES ${meshPly_SRC})


source_group("simulation\\geometry" FILES ${geometry_SRC})
set(simulationSource ${simulationSource} ${geometry_SRC}  )

set(boundingVolumes_SRC
 ./Geometry/BoundingVolumes/BoundingSphere.h
 ./Geometry/BoundingVolumes/BoundingSphere.cpp
 ./Geometry/BoundingVolumes/BoundingVolume.h
 ./Geometry/BoundingVolumes/BoundingVolume.cpp
 ./Geometry/BoundingVolumes/BoundingBox.h
 ./Geometry/BoundingVolumes/BoundingBox.cpp 
 ./Geometry/BoundingVolumes/BoundingOctree.h
 ./Geometry/BoundingVolumes/BoundingOctree.cpp 
)
source_group("simulation\\geometry\\boundingvolumes" FILES ${boundingVolumes_SRC})
set(simulationSource ${simulationSource} ${boundingVolumes_SRC}  )

set(geometryPrimitives_SRC
 ./Geometry/Primitives/Cylinder.h
 ./Geometry/Primitives/Cylinder.cpp
 ./Geometry/Primitives/Hexahedron.h
 ./Geometry/Primitives/Hexahedron.cpp
 ./Geometry/Primitives/Sphere.h
 ./Geometry/Primitives/Sphere.cpp
 ./Geometry/Primitives/Rectangle.h
 ./Geometry/Primitives/Rectangle.cpp
 ./Geometry/Primitives/Pyramid.h
 ./Geometry/Primitives/Pyramid.cpp
 ./Geometry/Primitives/Triangle.h
 ./Geometry/Primitives/Triangle.cpp
)

source_group("simulation\\geometry\\primitives" FILES ${geometryPrimitives_SRC})
set(simulationSource ${simulationSource} ${geometryPrimitives_SRC}  )

set(polygon_SRC
 ./Geometry/Polygon/Polygon.h
 ./Geometry/Polygon/Polygon.cpp
 ./Geometry/Polygon/Vertex.h
 ./Geometry/Polygon/Vertex.cpp
 ./Geometry/Polygon/HalfEdge.h
 ./Geometry/Polygon/HalfEdge.cpp
 ./Geometry/Polygon/Edge.h
 ./Geometry/Polygon/Edge.cpp
 ./Geometry/Polygon/Face.h
 ./Geometry/Polygon/Face.cpp
 ./Geometry/Polygon/Element.h
 ./Geometry/Polygon/Element.cpp
)
source_group("simulation\\geometry\\polygon" FILES ${polygon_SRC})
set(simulationSource ${simulationSource} ${polygon_SRC} ${meshPly_SRC} ${mesh_SRC})


