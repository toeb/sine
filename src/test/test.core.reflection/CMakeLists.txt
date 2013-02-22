
set(source
	 main.cpp 
	 reflection.cpp
	 type.cpp
	 argument.cpp
	 methodinfo.cpp
	 constructorinfo.cpp
	 propertyinfo.cpp
 )
 source_group("" FILES ${source})
 add_executable(test.core.reflection ${source} CMakeLists.txt)
 target_link_libraries(test.core.reflection core.testing  core.logging core)
 project_folder("test" test.core.reflection )
 
 add_test(NAME test.core.reflection COMMAND test.core.reflection)