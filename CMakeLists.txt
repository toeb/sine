cmake_minimum_required(VERSION 2.4)
 if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
 endif(COMMAND cmake_policy)
 
 
#SET(CMAKE_SUPPRESS_REGENERATION "1")

#ds = dynamische simulation
project(ds)

# enables testing for the projects.
include(CTest)
if(BUILD_TESTING)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  mark_as_advanced(BUILDNAME)
endif(BUILD_TESTING)

# set the root project folder for visual studio
set(dslibProjectFolder "")
# sets which projects not to build
set(dslibIgnoredProjects)
#set the project folder for externals
set(dslibExternalsProjectFolder "externals")

#causes freeglut to be built as a static lib
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

 SET(CMAKE_MODULE_PATH "${cmakeScriptsDirectory}")

# 1 for ibds classes 2 for dslib 3 for eigen 
add_definitions(-DMATRIX_CLASSES=2)

if (CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x  -std=gnu++0x -fopenmp -Wno-sign-compare ")
  SET(CMAKE_CXX_RELEASE_FLAGS "${CMAKE_CXX_RELEASE_FLAGS} -O3 -msse2 -std=c++0x  -std=gnu++0x -fopenmp -Wno-sign-compare ")

endif(CMAKE_COMPILER_IS_GNUCC)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj ")	
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ob2 /Oi /Ot /GL /bigobj " )
  SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif(MSVC)


include(${cmakeScriptsDirectory}/Common.cmake)
include(${cmakeScriptsDirectory}/AntTweakBar.cmake)      


include_directories(${sourceDirectory}/include)
include_directories(${externalsDirectory})
include_directories(${externalsDirectory}/freeglut/include)
include_directories(${externalsDirectory}/soil/src)
include_directories(${externalsDirectory}/lodepng)
include_directories(${externalsDirectory}/eigen3)
include_directories(${externalsDirectory}/cppunitlite)


include_directories(${externalsDirectory}/v8/include)


subdirs(externals)

include_directories(${includeDirectories})
subdirs(src)
