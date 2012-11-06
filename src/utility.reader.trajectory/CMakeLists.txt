set(source 
 ./TrajectoryReader.h
 ./TrajectoryReader.cpp
 ../include/utility.reader.trajectory.h
)


source_group("" FILES ${source})
add_library(utility.reader.trajectory ${source} CMakeLists.txt)
target_link_libraries(utility.reader.trajectory utility.reader math)
