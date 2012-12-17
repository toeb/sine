set(source 
 ./Task.h
 ./Task.cpp
 ./ExtendedTask.h
 ./ExtendedTask.cpp
 ./ScheduledTask.h
 ./ScheduledTask.cpp
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
 ./ScheduledTaskRunner.h
 ./ScheduledTaskRunner.cpp
 ./ScheduledTaskDelegate.h
 ./ScheduledTaskDelegate.cpp
 ./TaskDelegate.h
 ./TaskDelegate.cpp
 ./TaskRunnerBase.h
 ./TaskRunnerBase.cpp
 ../include/core.task.h
)

source_group("" FILES ${source})
add_library(core.task ${source} CMakeLists.txt)
target_link_libraries(core.task core)