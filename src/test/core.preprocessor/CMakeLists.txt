
set(source
	 main.cpp 
	 tests.cpp
	 

 )
 source_group("" FILES ${source})
 add_executable(test.core.preprocessor ${source} CMakeLists.txt)
 target_link_libraries(test.core.preprocessor core.testing  core.logging core)
 project_folder("test" test.core.preprocessor )
 
 add_test(NAME test.core.preprocessor COMMAND test.core.preprocessor)