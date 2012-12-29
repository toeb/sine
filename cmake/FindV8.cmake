MESSAGE(STATUS "Looking for v8")
FIND_PATH(V8_INCLUDE_PATH
        NAMES
                v8.h
        PATHS
				${externalsDirectory}/v8/include
                NO_DEFAULT_PATH)

				
FIND_LIBRARY(V8_LIBRARY_PATH
        NAMES
                v8_base v8_snapshot v8_nosnapshot preparser_lib
        PATHS
				${externalsDirectory}/v8/build/Debug/lib
                NO_DEFAULT_PATH)
				
IF(V8_INCLUDE_PATH)
        SET(V8_FOUND 1 CACHE STRING "Set to 1 if v8 is found, 0 otherwise")
        MESSAGE(STATUS "Looking for v8 headers - found")
ELSE(V8_INCLUDE_PATH)
        SET(V8_FOUND 0 CACHE STRING "Set to 1 if v8 is found, 0 otherwise")
        MESSAGE(STATUS "Looking for v8 headers - not found")
ENDIF(V8_INCLUDE_PATH)

IF(V8_LIBRARY_PATH)
        SET(V8_FOUND 1 CACHE STRING "Set to 1 if v8 is found, 0 otherwise")
        MESSAGE(STATUS "Looking for v8 library - found")
ELSE(V8_LIBRARY_PATH)
        SET(V8_FOUND 0 CACHE STRING "Set to 1 if v8 is found, 0 otherwise")
        MESSAGE(STATUS "Looking for v8 library - not found")
ENDIF(V8_LIBRARY_PATH)

MARK_AS_ADVANCED(V8_FOUND)