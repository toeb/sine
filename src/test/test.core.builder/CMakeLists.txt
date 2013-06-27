
set(source
test.cpp
)
source_group("" FILES ${source})
add_executable(test.core.builder ${source} CMakeLists.txt)
target_link_libraries(test.core.builder 
	application.console.testing 
	core.builder
)
 
add_test(NAME test.core.builder COMMAND test.core.builder)