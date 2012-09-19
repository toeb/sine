add_executable(sample.imaging main.cpp)
target_link_libraries(sample.imaging lodepng math common core time)
project_folder("samples" sample.imaging)