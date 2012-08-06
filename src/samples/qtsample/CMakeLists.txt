add_executable(qtsample main.cpp)
target_link_libraries(qtsample qtrunner simulationUtilities glrenderers opengl dynamics force visualization geometry soil lodepng)
project_folder("samples" qtsample )