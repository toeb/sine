
set(source
test.cpp
)
source_group("" FILES ${source})
add_executable(test.core.task.scheduling  ${source} CMakeLists.txt)
target_link_libraries(test.core.task.scheduling 
	application.console.testing 
	core.logging 
	core.task 
)
 
add_test(NAME test.core.task.scheduling  COMMAND test.core.task.scheduling )