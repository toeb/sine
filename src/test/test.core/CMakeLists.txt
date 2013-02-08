set(source
 tests.cpp
 main.cpp 
 set.cpp
 reflection.cpp
 conversion.h
 conversion.cpp
 )
 source_group("" FILES ${source})
 add_executable(test.core ${source} CMakeLists.txt)
 target_link_libraries(test.core core.testing core core.serialization core.reflection)

 project_folder("test" test.core )


 
 add_test(NAME test.core COMMAND test.core)