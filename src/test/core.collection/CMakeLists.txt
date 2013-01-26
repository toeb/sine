set(source
 tests.cpp
 main.cpp 
)
 source_group("" FILES ${source})
 add_executable(test.core.collection ${source} CMakeLists.txt)
 target_link_libraries(test.core.collection core.testing  core)
 project_folder("test" test.core.collection )

 
 add_test(NAME test.core.collection COMMAND test.core.collection)