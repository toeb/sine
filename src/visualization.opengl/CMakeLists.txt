


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

source_group("src" FILES ${opengl_SRC})
add_library(opengl   ${opengl_SRC} )
project_folder("visualization/gl" opengl)


find_package(OpenGL REQUIRED)


include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
target_link_libraries(opengl kinematics integration freeglut  ${OPENGL_LIBRARIES} )


