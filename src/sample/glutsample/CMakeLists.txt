add_executable(sample.glut main.cpp)
project_folder("samples" sample.glut)
target_link_libraries(sample.glut simulation.runner.glut)