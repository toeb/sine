
find_package(OpenGL)
find_package(OpenGL)
if(OPENGL_FOUND)

  include_directories(${OPENGL_INCLUDE_DIR})
  
 # set(meshrenderers_SRC
 #  ./mesh/Mesh.h
 #  ./mesh/Mesh.cpp
 #  ./mesh/MeshRenderer.h
 #  ./mesh/MeshRenderer.cpp
 #  ./mesh/CubeMesh.h
 #  ./mesh/CubeMesh.cpp
 #  ./mesh/SphereMesh.h
 #  ./mesh/SphereMesh.cpp   
 #  ./mesh/PlaneMesh.h
 #  ./mesh/PlaneMesh.cpp
 #  ./mesh/PlyMesh.h
 #  ./mesh/PlyMesh.cpp
 #  ./mesh/rply.h
 #  ./mesh/rply.c
 # )
 # set(renderers_General_SRC 
 #  ./general/CoordinateSystemRenderer.h
 #  ./general/CoordinateSystemRenderer.cpp
 #  ./general/VectorRenderer.cpp
 #  ./general/VectorRenderer.h
 #  ./general/GridRenderer.h
 #  ./general/GridRenderer.cpp
 #  ./general/OffsetRenderer.h
 #  ./general/OffsetRenderer.cpp
 #  ./general/LightRenderer.h
 #  ./general/LightRenderer.cpp
 # )
  set(opengl_SRC
   ./MiniGL.h
   ./MiniGL.cpp
   ./opengl.h
   ./OpenGLRenderModule.h
   ./OpenGLRenderModule.cpp
   ./GlViewport.h
   ./GlViewport.cpp
   ./Utility.h
   ./Utility.cpp
   ./FpsCamera.h
   ./FpsCamera.cpp
   ./GlMaterial.h
   ./GlMaterial.cpp
   ./GlTexture.h
   ./GlTexture.cpp
  )
  
  source_group("src\\general" FILES ${renderers_General_SRC})
  source_group("src" FILES ${opengl_SRC})
  source_group("src\\mesh" FILES ${meshrenderers_SRC})
  
  add_library(opengl   ${opengl_SRC} ${meshrenderers_SRC} ${renderers_General_SRC} ${renderers_Simple_SRC})
  project_folder("visualization/gl" opengl)
  
  target_link_libraries(opengl kinematics integration freeglut ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
  
else(OPENGL_FOUND)
  message("cannot find opengl")
endif(OPENGL_FOUND)
