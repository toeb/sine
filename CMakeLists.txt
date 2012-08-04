cmake_minimum_required(VERSION 2.4)
#SET(CMAKE_SUPPRESS_REGENERATION "1")

#ds = dynamische simulation
project(ds)

set(projectPath ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${projectPath}/build/lib)
set(EXECUTABLE_OUTPUT_PATH ${projectPath}/build/bin)
set(sourceDirectory ${projectPath}/src)
set(externalsDirectory ${projectPath}/externals)
set(cmakeScriptsDirectory ${projectPath}/cmake)

set(includeDirectories ${sourceDirectory})

include(${cmakeScriptsDirectory}/Common.cmake)
include(${cmakeScriptsDirectory}/AntTweakBar.cmake)      

include_directories(${externalsDirectory})
include_directories(${externalsDirectory}/freeglut/include)
include_directories(${externalsDirectory}/soil/src)
include_directories(${externalsDirectory}/lodepng)


subdirs(externals)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
add_definitions(-DQT)
include(${QT_USE_FILE})
message(${includeDirectories})
include_directories(${includeDirectories})
subdirs(src)