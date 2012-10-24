set(source 
./Log.h
./Log.cpp
)
source_group("" FILES ${source})
add_library(simulation.logging ${source} CMakeLists.txt)
target_link_libraries(simulation.logging core)