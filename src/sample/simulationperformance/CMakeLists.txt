add_executable(simulationperformance main.cpp)
target_link_libraries(simulationperformance consolerunner simulationUtilities dynamics force geometry)
project_folder("samples" simulationperformance )