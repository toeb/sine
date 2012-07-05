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
	./Core/Time.h
	./Core/Time.cpp
)
set(controlSource
	./Core/Control/CommandModule.h
	./Core/Control/CommandModule.cpp
	./Core/Control/Command.h
	./Core/Control/Command.cpp
	./Core/Control/CommandListener.h
	./Core/Control/CommandListener.cpp
)

source_group("simulation\\core\\control" FILES ${controlSource})
set(timingSource
	./Core/Timing/TimingModule.h
	./Core/Timing/TimingModule.cpp
	./Core/Timing/Timeable.h
	./Core/Timing/Timeable.cpp
	./Core/Timing/Timer.h
	./Core/Timing/Timer.cpp
)
source_group("simulation\\core\\timing" FILES ${timingSource})
set(simulationSource ${simulationSource} ${coreSource} ${controlSource} ${timingSource}  )
source_group("simulation\\core" FILES ${coreSource})
