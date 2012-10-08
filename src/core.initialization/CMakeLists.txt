set(source
 ./Initializable.h
 ./Initializable.cpp
 ./InitializationModule.h
 ./InitializationModule.cpp
 ../include/core.initialization.h
 )
 
 source_group("" FILES ${source})
 add_library(core.initialization ${source} CMakeLists.txt)
 target_link_libraries(core.initialization simulation)
 