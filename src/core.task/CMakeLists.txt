set(source 
 ./Task.h
 ./Task.cpp
 ./ExtendedTask.h
 ./ExtendedTask.cpp
 ./ITask.h
 ./ITask.cpp
 ./ITaskRunner.h
 ./ITaskRunner.cpp
 ./ImmediateTaskRunner.h
 ./ImmediateTaskRunner.cpp
 ./SerialTaskRunner.h
 ./SerialTaskRunner.cpp
 ./ParallelTaskRunner.h
 ./ParallelTaskRunner.cpp
)

source_group("" FILES ${source})
add_library(core.task ${source} CMakeLists.txt)
target_link_libraries(core.task core)