add_executable(qtsample main.cpp)
target_link_libraries(qtsample qtrunner simulationUtilities glrenderers opengl visualization geometry)
project_folder("samples" qtsample )