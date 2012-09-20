cmake_minimum_required(VERSION 2.4)
 if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
 endif(COMMAND cmake_policy)
 
#SET(CMAKE_SUPPRESS_REGENERATION "1")

#ds = dynamische simulation
project(ds)

set(defaultProjectFolder "dslib")
add_definitions(-DFREEGLUT_LIB_PRAGMAS=0)
add_definitions(-DFREEGLUT_STATIC=1)

set(projectPath ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${projectPath}/build/lib)
set(EXECUTABLE_OUTPUT_PATH ${projectPath}/build/bin)
set(sourceDirectory ${projectPath}/src)
set(externalsDirectory ${projectPath}/externals)
set(cmakeScriptsDirectory ${projectPath}/cmake)
set(resourceDirectory ${projectPath}/resources)

set(includeDirectories ${sourceDirectory})



IF (CMAKE_COMPILER_IS_GNUCC)
  ##use c++0x flags for gcc (needed for the new integrators)
  add_definitions(" -std=c++0x ")
  add_definitions(" -std=gnu++0x ")

ENDIF(CMAKE_COMPILER_IS_GNUCC)


include(${cmakeScriptsDirectory}/Common.cmake)
include(${cmakeScriptsDirectory}/AntTweakBar.cmake)      


include_directories(${externalsDirectory})
include_directories(${externalsDirectory}/freeglut/include)
include_directories(${externalsDirectory}/soil/src)
include_directories(${externalsDirectory}/lodepng)
include_directories(${externalsDirectory}/eigen3)

subdirs(externals)

include_directories(${includeDirectories})
subdirs(src)
