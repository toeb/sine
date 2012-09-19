set(source
 ./Initializable.h
 ./Initializable.cpp
 ./InitializationModule.h
 ./InitializationModule.cpp
 )
 
 source_group("" FILES ${source})
 add_library(initialization ${source} CMakeLists.txt)
 project_folder("simulation/modules" initialization)
 