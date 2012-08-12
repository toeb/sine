add_executable(imaging main.cpp)
target_link_libraries(imaging lodepng math common core time)
project_folder("samples" imaging)