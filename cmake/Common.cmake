option(USE_DOUBLE_PRECISION "Use double precision"	ON)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)
SET(CMAKE_DEBUG_POSTFIX "d")

IF (WIN32)
   SET(CMAKE_USE_RELATIVE_PATHS "1")
	# Set compiler flags for "release"
	SET(CMAKE_CXX_FLAGS_RELEASE "/MD /Ox /Ob2 /Oi /Ot /GL /D NDEBUG") 
	SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG")
	SET(IBDS_STATIC_LIBRARY_FLAGS_RELEASE "/INCREMENTAL:NO /LTCG")
ENDIF (WIN32)

IF (UNIX)
     SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin/${CMAKE_BUILD_TYPE})
ENDIF (UNIX)

IF (USE_DOUBLE_PRECISION)
	ADD_DEFINITIONS( -DUSE_DOUBLES)	
ENDIF (USE_DOUBLE_PRECISION)

ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)

#macro for setting project folders (only for visual studio)
macro(project_folder folder projects)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
foreach(proj ${projects}) 
	SET_PROPERTY(TARGET ${proj} PROPERTY FOLDER ${folder})
endforeach(proj)
endmacro()

#macro for copyng resources to a target
macro (resources targetName )    
add_custom_command(TARGET ${targetName} POST_BUILD        	# Adds a post-build event to resources
 COMMAND ${CMAKE_COMMAND} -E copy_directory    		  
 "${RESOURCE_DIR}"      								# <--this is in-path
  $<TARGET_FILE_DIR:${targetName}>)                 		# <--this is out-file path
endmacro()


MACRO(subdirlist result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        SET(dirlist ${dirlist} ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
