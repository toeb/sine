
set(source
test.cpp
)
source_group("" FILES ${source})
add_executable(test.core.injection ${source} CMakeLists.txt)
target_link_libraries(test.core.injection 
	application.console.testing 
	core.injection
)
 
add_test(NAME test.core.injection COMMAND test.core.injection)