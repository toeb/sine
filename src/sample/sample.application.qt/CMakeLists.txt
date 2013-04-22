set(source main.cpp)

add_executable(sample.application.qt ${source})
target_link_libraries(sample.application.qt application.qt)

## include qt include files for gui
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)

include(${QT_USE_FILE})
project_folder("samples" sample.application.qt)

