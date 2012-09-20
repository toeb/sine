add_executable(sample.performance.simulation main.cpp)
target_link_libraries(sample.performance.simulation 
simulation.runner.console 
simulation.utility
simulation.dynamics 
simulation.dynamics.force 
simulation.geometry)
project_folder("samples" sample.performance.simulation )