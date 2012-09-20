set(source
	IInputListener.h
	IInputListener.cpp
	InputHandler.h
	InputHandler.cpp
	Keys.h
	Keys.cpp
)
source_group("src" FILES ${source})
add_library(simulation.interaction ${source} CMakeLists.txt)
target_link_libraries(simulation.interaction  simulation)