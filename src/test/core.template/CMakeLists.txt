
set(source
	 main.cpp 
	 tests.cpp

 )
 source_group("" FILES ${source})
 add_executable(test.core.template ${source} CMakeLists.txt)
 target_link_libraries(test.core.template core.testing  core.logging core)
 project_folder("test" test.core.template )
 
 add_test(NAME test.core.template COMMAND test.core.template)