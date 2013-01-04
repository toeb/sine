
set(source 
 main.cpp
)

add_executable(sample.matrix ${source} CMakeLists.txt)

target_link_libraries(sample.matrix math)
project_folder("samples" sample.matrix)