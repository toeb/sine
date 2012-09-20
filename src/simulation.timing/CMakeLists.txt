set(source
 ./Timeable.h
 ./Timeable.cpp
 ./TimingModule.h
 ./TimingModule.cpp
)

source_group("" FILES ${source})
add_library(simulation.timing ${source})
target_link_libraries(simulation.timing simulation)
