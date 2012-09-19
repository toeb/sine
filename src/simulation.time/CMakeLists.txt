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
)

source_group("src" FILES ${timeSource})

add_library(time ${timeSource} CMakeLists.txt)
target_link_libraries(time core common)
project_folder("simulation/utility" time)