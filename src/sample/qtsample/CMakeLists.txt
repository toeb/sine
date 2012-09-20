find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
add_definitions(-DQT)
include(${QT_USE_FILE})

add_executable(sample.qt main.cpp)
target_link_libraries(sample.qt
 simulation.runner.qt
 simulation.utility
 simulation.dynamics
 simulation.dynamics.force
 simulation.geometry
 visualization.opengl.renderer
 utility.reader.urdf
 simulation.dynamics.multibody.impulsebased math)
project_folder("samples" sample.qt )
