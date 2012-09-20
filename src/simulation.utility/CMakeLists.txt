set(source
./DefaultSimulationSetup.h
./DefaultSimulationSetup.cpp
#./SimulationBuilder.h
#./SimulationBuilder.cpp
./DynamicsAlgorithm.h
./DynamicsAlgorithm.cpp

)
source_group("" FILES ${source})
add_library(simulation.utility ${source} CMakeLists.txt)
target_link_libraries(simulation.utility 
simulation.time 
simulation.integration 
visualization
simulation
simulation.dynamics 
simulation.dynamics.multibody.impulsebased
simulation.dynamics.force)

