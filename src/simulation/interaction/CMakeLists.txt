set(source
	IInputListener.h
	IInputListener.cpp
	InputHandler.h
	InputHandler.cpp
	Keys.h
	Keys.cpp
)
source_group("src" FILES ${source})
add_library(interaction ${source} CMakeLists.txt)
project_folder("simulation/modules" interaction)
target_link_libraries(interaction core math)