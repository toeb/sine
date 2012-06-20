cmake_minimum_required(VERSION 2.4)
SET(CMAKE_SUPPRESS_REGENERATION "1")

PROJECT(Simulation)

SET(PROJECT_PATH ${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

INCLUDE(${PROJECT_PATH}/CMake/Common.cmake)
INCLUDE(${PROJECT_PATH}/CMake/AntTweakBar.cmake)      

SUBDIRS(freeglut Math Simulation Visualization Samples)





