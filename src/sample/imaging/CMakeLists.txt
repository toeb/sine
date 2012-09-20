add_executable(sample.imaging main.cpp)
target_link_libraries(sample.imaging lodepng math core simulation simulation.time)
project_folder("samples" sample.imaging)
