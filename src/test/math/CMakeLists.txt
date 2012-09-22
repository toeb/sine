set(source
 tests.cpp
 integrators.cpp
 matrix.cpp
 vector.cpp
 quaternion.cpp
 scalar.cpp
 main.cpp 
 )
 source_group("" FILES ${source})
 add_executable(test.math ${source} CMakeLists.txt)
 target_link_libraries(test.math cppunitlite math math.integration math.matrix math.matrix.dslib)
 project_folder("test" test.math )