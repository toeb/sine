
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
include(${QT_USE_FILE})



set(source 
 main.cpp
)

add_executable(sample.simple ${source} CMakeLists.txt)

target_link_libraries(sample.simple application.sample simulation.dynamics simulation.dynamics.force simulation.dynamics.textile simulation.utility utility.reader.trajectory)
project_folder("samples" sample.simple)