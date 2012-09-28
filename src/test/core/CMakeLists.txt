set(source
 tests.cpp
 main.cpp 
 set.cpp
 )
 source_group("" FILES ${source})
 add_executable(test.core ${source} CMakeLists.txt)
 target_link_libraries(test.core cppunitlite  core)
 project_folder("test" test.core )