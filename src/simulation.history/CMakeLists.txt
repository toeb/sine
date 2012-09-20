set(source
 ./HistoryModule.h
 ./HistoryModule.cpp
 ./StateSnapshot.h
 ./StateSnapshot.cpp
)
source_group("src" FILES ${source})
add_library(simulation.history ${source} CMakeLists.txt)
target_link_libraries(simulation.history simulation.integration simulation)