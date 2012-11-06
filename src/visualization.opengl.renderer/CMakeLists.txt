set(source
 ./VectorRenderer.h
 ./VectorRenderer.cpp
 ./BillboardRenderer.h
 ./BillboardRenderer.cpp
 ./OffsetRenderer.h
 ./OffsetRenderer.cpp
 ./LightRenderer.h
 ./LightRenderer.cpp
 ./DefaultLightSetup.h
 ./DefaultLightSetup.cpp
 ./CameraRenderer.h
 ./CameraRenderer.cpp
 ./GridRenderer.h
 ./GridRenderer.cpp
 ./MeshGridRenderer.h
 ./MeshGridRenderer.cpp
 ./SkyboxRenderer.h
 ./SkyboxRenderer.cpp
 ./ShadowMapper.h
 ./ShadowMapper.cpp
 ../include/visualization.opengl.renderer.h
)
source_group("" FILES ${source})

add_library(visualization.opengl.renderer CMakeLists.txt ${source})

target_link_libraries(visualization.opengl.renderer
visualization.opengl 
simulation
simulation.kinematics
utility.imaging
)

