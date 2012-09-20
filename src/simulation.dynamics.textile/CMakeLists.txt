SET(source
./TextileModel.h
./TextileModel.cpp
./TextileAlgorithm.h
./TextileAlgorithm.cpp
)

source_group("" FILES ${source})
add_library(simulation.dynamics.textile ${source} CMakeLists.txt)
target_link_libraries(simulation.dynamics.textile
 simulation.dynamics)
