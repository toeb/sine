set(source 
	./Collision.h
	./Collision.cpp
	./Collidable.h
	./Collidable.cpp
	./Contact.h
	./Contact.cpp
	./ICollidable.h
)
source_group("" FILES ${source})

add_library(simulation.collision ${source} CMakeLists.txt)
target_link_libraries(simulation.collision simulation)