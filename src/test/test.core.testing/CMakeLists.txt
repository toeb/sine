set(source tests.cpp)
 source_group("" FILES ${source})
add_executable(test.core.testing ${source} CMakeLists.txt)
 
 target_link_libraries(test.core.testing core.testing)
 
 project_folder("test" test.core.testing )
 add_test(NAME test.core.testing COMMAND test.core.testing)