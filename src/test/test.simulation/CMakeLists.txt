set(source
 tests.cpp
 main.cpp 
 )
 source_group("" FILES ${source})
 add_executable(test.simulation ${source} CMakeLists.txt)
 target_link_libraries(test.simulation core.testing )
 project_folder("test" test.simulation )
 
 add_test(NAME test.simulation COMMAND test.simulation)