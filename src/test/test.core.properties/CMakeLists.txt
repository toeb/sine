
set(source
	 main.cpp 
	 tests.cpp
	 

 )
 source_group("" FILES ${source})
 add_executable(test.core.properties ${source} CMakeLists.txt)
 target_link_libraries(test.core.properties core.testing  core.logging core)
 project_folder("test" test.core.properties )
 
 add_test(NAME test.core.properties COMMAND test.core.properties)