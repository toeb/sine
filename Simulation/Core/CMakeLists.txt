set(coreSource
	./Core/CompositeSimulationObject.h
	./Core/CompositeSimulationObject.cpp
	./Core/ISimulationModule.h
	./Core/Simulation.h
	./Core/Simulation.cpp
	./Core/CompositeSimulationModule.h
	./Core/CompositeSimulationModule.cpp	
	./Core/SimulationModuleBase.h
	./Core/SimulationModuleBase.cpp
	./Core/ISimulationObject.h
	./Core/ISimulationObject.cpp
	./Core/IUpdateable.h
	./Core/IUpdateable.cpp
	./Core/UpdateablesModule.h
	./Core/UpdateablesModule.cpp	
	./Core/ValueHolder.h
	
)
set(simulationSource ${simulationSource} ${coreSource}  )
source_group("simulation\\core" FILES ${coreSource})
