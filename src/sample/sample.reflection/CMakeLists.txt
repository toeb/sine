add_executable(sample.reflection main.cpp)
target_link_libraries(sample.reflection core.reflection )
project_folder("samples" sample.reflection core.reflection ) 