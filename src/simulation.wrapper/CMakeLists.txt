set(source 
./DelegateWrapper.h
./DelegateWrapper.cpp
./Wrapper.h
./Wrapper.cpp
./WrapperModule.h
./WrapperModule.cpp
)

source_group("" FILES ${source})
add_library(simulation.wrapper ${source} CMakeLists.txt)
target_link_libraries(simulation.wrapper simulation)