set(source
./CMakeLists.txt
./IStatefulObject.h
./State.h
./State.cpp
./CompositeStatefulObject.h
./CompositeStatefulObject.cpp
)

source_group("" FILES ${source})

add_library(simulation.state ${source})
target_link_libraries(simulation.state simulation math)