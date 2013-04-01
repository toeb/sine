add_executable(sample.mathgl main.cpp)
target_link_libraries(sample.mathgl core core.reflection )
project_folder("samples" sample.mathgl core core.reflection ) 