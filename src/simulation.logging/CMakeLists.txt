set(source 
./LoggingObject.h
./LoggingObject.cpp
./LoggingModule.h
./LoggingModule.cpp
)
source_group("" FILES ${source})
add_library(simulation.logging ${source} CMakeLists.txt)
target_link_libraries(simulation.logging simulation)