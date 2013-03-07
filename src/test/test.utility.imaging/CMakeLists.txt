set(source
	tests.cpp
	main.cpp 
)
 source_group("" FILES ${source})
 add_executable(test.utility.imaging ${source} CMakeLists.txt)
 target_link_libraries(test.utility.imaging core.testing  core utility.imaging)
 project_folder("test" test.utility.imaging )

 
 add_test(NAME test.utility.imaging COMMAND test.utility.imaging)