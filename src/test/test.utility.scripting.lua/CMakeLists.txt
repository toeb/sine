
set(source
	 main.cpp 
	 tests.cpp
 )
 source_group("" FILES ${source})
 add_executable(test.scripting.lua ${source} CMakeLists.txt)
 target_link_libraries(test.scripting.lua core.testing  core.logging core scripting.lua)
 project_folder("test" test.scripting.lua )
 
 add_test(NAME test.scripting.lua COMMAND test.scripting.lua)