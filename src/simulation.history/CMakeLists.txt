set(source
 ./HistoryModule.h
 ./HistoryModule.cpp
 ./StateSnapshot.h
 ./StateSnapshot.cpp
)
source_group("src" FILES ${source})
add_library(history ${source} CMakeLists.txt)
project_folder("simulation/modules" history)