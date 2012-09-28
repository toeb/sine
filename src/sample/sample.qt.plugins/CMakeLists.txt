
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
add_definitions(-DQT)
include(${QT_USE_FILE})

set(source 
 main.cpp
)

add_executable(sample.qt.plugins ${source} CMakeLists.txt)


target_link_libraries(sample.qt.plugins simulation.runner.qt simulation.time visualization.opengl.renderer.geometry)

project_folder("samples" sample.qt.plugins)