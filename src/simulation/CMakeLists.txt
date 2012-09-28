set(coreSource
	./ISimulationModule.h
	./Simulation.h
	./Simulation.cpp	
	./SimulationModuleBase.h
	./SimulationModuleBase.cpp
	./ISimulationObject.h
	./ISimulationObject.cpp
	./SimulationTask.h
../config.h
)
source_group("src" FILES ${coreSource})


set(compositeSource
 ./composites/CompositeSimulationObject.h
 ./composites/CompositeSimulationObject.cpp
 ./composites/CompositeSimulationModule.h
 ./composites/CompositeSimulationModule.cpp
)

source_group("src\\composites" FILES ${compositeSource})

add_library(simulation  ${coreSource} ${compositeSource})
target_link_libraries(simulation math core core.task core.initialization)
