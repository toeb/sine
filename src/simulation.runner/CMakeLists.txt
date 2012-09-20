set(source
	./SimulationRunner.h
	./SimulationRunner.cpp
)
source_group("src" FILES ${source})

add_library(simulation.runner  ${source})
target_link_libraries(simulation.runner simulation)