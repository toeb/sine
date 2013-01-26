set(source
 tests.cpp
 main.cpp 
 )
 source_group("" FILES ${source})
 add_executable(test.core.hub ${source} CMakeLists.txt)
 
 target_link_libraries(test.core.hub core.testing  core.hub)
 
 project_folder("test" test.core.hub )
 add_test(NAME test.core.hub COMMAND test.core.hub)