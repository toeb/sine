INCLUDE_DIRECTORIES(${externalsDirectory}/AntTweakBar)
LINK_DIRECTORIES(${externalsDirectory}/AntTweakBar)
IF (CMAKE_CL_64)	
	SET(ANTTWEAKBAR_LIB_NAME AntTweakBar64)		
ELSE (CMAKE_CL_64)
	SET(ANTTWEAKBAR_LIB_NAME AntTweakBar)
ENDIF (CMAKE_CL_64)	
SET(ANTTWEAKBAR_LIBS ${ANTTWEAKBAR_LIB_NAME}.lib)

# A macro for copying the solid dll
MACRO(COPY_ANTTWEAKBAR_DLL targetName)
	IF (WIN32)
		ADD_CUSTOM_COMMAND(
		   TARGET ${targetName}
		   POST_BUILD
		   COMMAND xcopy /r /y \"${PROJECT_PATH}/AntTweakBar\\${ANTTWEAKBAR_LIB_NAME}.dll" \"$\(TargetDir\)..\\..\\bin\\$\(ConfigurationName\)\\"
		)                        
	ENDIF (WIN32)
ENDMACRO(COPY_ANTTWEAKBAR_DLL)	