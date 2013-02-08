set(source tests.cpp)
 source_group("" FILES ${source})
add_executable(test.core.base ${source} CMakeLists.txt)
 
 target_link_libraries(test.core.base core)
 
 project_folder("test" test.core.base )
 add_test(NAME test.core.base COMMAND test.core.base)