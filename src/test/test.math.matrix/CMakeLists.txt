add_executable(test.math.matrix main.cpp tests.cpp CMakeLists.txt)

target_link_libraries(test.math.matrix core.testing math math.integration math.matrix math.matrix.dslib)
 project_folder("test" test.math.matrix )
