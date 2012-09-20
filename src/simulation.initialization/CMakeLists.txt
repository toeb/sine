set(source
 ./Initializable.h
 ./Initializable.cpp
 ./InitializationModule.h
 ./InitializationModule.cpp
 )
 
 source_group("" FILES ${source})
 add_library(simulation.initialization ${source} CMakeLists.txt)
 target_link_libraries(simulation.initialization simulation)
 