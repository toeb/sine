set(source
 tests.cpp
 main.cpp 
 )
 source_group("" FILES ${source})
 add_executable(test.math ${source} CMakeLists.txt)
 target_link_libraries(test.math cppunitlite math math.linearalgebra math.linearalgebra.dslib)
 project_folder("test" test.math )