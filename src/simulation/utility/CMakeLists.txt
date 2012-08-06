set(source
./DefaultSimulationSetup.h
./DefaultSimulationSetup.cpp
#./SimulationBuilder.h
#./SimulationBuilder.cpp
./DynamicsAlgorithm.h
./DynamicsAlgorithm.cpp

)
source_group("src" FILES ${source})
add_library(simulationUtilities ${source} CMakeLists.txt)
target_link_libraries(simulationUtilities time integration visualization core)
project_folder("simulation" simulationUtilities)

