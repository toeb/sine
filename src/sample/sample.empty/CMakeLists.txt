add_executable(sample.empty main.cpp)
target_link_libraries(sample.empty core core.reflection )
project_folder("samples" sample.empty core core.reflection ) 