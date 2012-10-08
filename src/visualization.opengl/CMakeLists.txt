set(source
./MiniGL.h
./MiniGL.cpp
./opengl.h
./OpenGLRenderModule.h
./OpenGLRenderModule.cpp
./GlViewport.h
./GlViewport.cpp
./Utility.h
./Utility.cpp
./GlMaterial.h
./GlMaterial.cpp
./GlTexture.h
./GlTexture.cpp
../visualization.opengl.h
)

source_group("" FILES ${source})
add_library(visualization.opengl   ${source} )

##opengl is required for visualization.opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

target_link_libraries(visualization.opengl
visualization
simulation.kinematics 
simulation.integration 
freeglut  
${OPENGL_LIBRARIES} )




