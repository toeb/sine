
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
include(${QT_USE_FILE})



set(source 
 main.cpp
)

add_executable(sample.scripting ${source} CMakeLists.txt)

target_link_libraries(sample.scripting application.sample simulation.dynamics simulation.dynamics.force simulation.dynamics.textile simulation.utility utility.reader.trajectory scripting.javascript scripting.lua scripting.ruby scripting.python)
project_folder("samples" sample.scripting)