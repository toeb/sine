
set(source
	 main.cpp 
	 tests.cpp
 )
 source_group("" FILES ${source})
 add_executable(test.scripting.python ${source} CMakeLists.txt)


find_package(PythonInterp)
find_package(PythonLibs)

include_directories(${PYTHON_INCLUDE_DIRS})
 
 target_link_libraries(test.scripting.python core.testing  core.logging core scripting.python ${PYTHON_LIBRARIES})
 project_folder("test" test.scripting.python )
 
 add_test(NAME test.scripting.python COMMAND test.scripting.python)