set(timeSource
	./ITimeProvider.h
	./ITimeProvider.cpp
	./SimulationTimeProvider.h
	./SimulationTimeProvider.cpp
	./RealTimeProvider.h
	./RealTimeProvider.cpp
	./PeriodicTask.h
	./PeriodicTask.cpp
	./SimulationTimeController.h
	./SimulationTimeController.cpp
	./CallbackTask.h
	./CallbackTask.cpp
	../include/simulation.time.h
)

source_group("src" FILES ${timeSource})

add_library(simulation.time ${timeSource} CMakeLists.txt)
target_link_libraries(simulation.time simulation)