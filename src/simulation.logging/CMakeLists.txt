set(source 
./LoggingObject.h
./LoggingObject.cpp
./LoggingModule.h
./LoggingModule.cpp
)
source_group("" FILES ${source})
add_library(logging ${source} CMakeLists.txt)
project_folder("simulation/modules" logging)