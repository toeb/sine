set(generalSource
 ./general/VectorRenderer.h
 ./general/VectorRenderer.cpp
 ./general/BillboardRenderer.h
 ./general/BillboardRenderer.cpp
 ./general/TextRenderer.h
 ./general/TextRenderer.cpp
 ./general/OffsetRenderer.h
 ./general/OffsetRenderer.cpp
 ./general/LightRenderer.h
 ./general/LightRenderer.cpp
 ./general/DefaultLightSetup.h
 ./general/DefaultLightSetup.cpp
 ./general/CameraRenderer.h
 ./general/CameraRenderer.cpp
 ./general/GridRenderer.h
 ./general/GridRenderer.cpp
 ./general/CoordinateSystemRenderer.h
 ./general/CoordinateSystemRenderer.cpp
)
source_group("general" FILES ${generalSource})
set(geometrySource
 ./geometry/SphereRenderer.h
 ./geometry/SphereRenderer.cpp
 ./geometry/PolygonRenderer.h
 ./geometry/PolygonRenderer.cpp
 ./geometry/PointRenderer.h
 ./geometry/PointRenderer.cpp
 ./geometry/PlaneRenderer.h
 ./geometry/PlaneRenderer.cpp
 ./geometry/BoxRenderer.h
 ./geometry/BoxRenderer.cpp
)
source_group("geometry" FILES ${geometrySource})
set(simulationSource)
source_group("simulation" FILES ${simulationSource})
set(tweakbarSource
 ./tweakbar/TweakBarRenderer.h
 ./tweakbar/TweakBarRenderer.cpp
)
source_group("tweakbar" FILES ${tweakbarSource})

add_library(visualization.opengl.renderer CMakeLists.txt ${generalSource} ${geometrySource} ${simulationSource} ${tweakbarSource})

target_link_libraries(visualization.opengl.renderer
visualization.opengl 
simulation
simulation.kinematics)

