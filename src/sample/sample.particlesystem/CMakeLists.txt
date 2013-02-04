
SET (QT_USE_QTDECLARATIVE TRUE)
SET (QT_USE_QTSCRIPT TRUE)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
#include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
include(${QT_USE_FILE})



set(source 
  main.cpp
)

add_executable(sample.particlesystem ${source} CMakeLists.txt)

target_link_libraries(sample.particlesystem 
  application.sample 
  simulation.dynamics 
  simulation.dynamics.force 
  simulation.dynamics.textile 
  simulation.utility 
  utility.reader.trajectory
  utility.reader.mesh
)

project_folder("samples" sample.particlesystem)