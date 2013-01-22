set(source 
  main.cpp
)

## include qt for gui
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${QT_USE_FILE})

add_executable(sample.mesh.render ${source} CMakeLists.txt)

target_link_libraries(sample.mesh.render application.sample simulation.geometry utility.reader.obj utility.reader.ply)
project_folder("samples" sample.mesh.render)