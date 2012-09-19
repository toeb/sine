set(source
	./SimulationRunner.h
	./SimulationRunner.cpp
)
source_group("src" FILES ${source})

add_library(runner ${source})
target_link_libraries(runner common core)
project_folder("simulation/modules" runner)