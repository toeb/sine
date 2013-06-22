
set(source
test.cpp
)
source_group("" FILES ${source})
add_executable(test.core.serialization ${source} CMakeLists.txt)
target_link_libraries(test.core.serialization 
	application.console.testing 
	core.logging 
	core.serialization 
	utility.serialization.json 
)
 
add_test(NAME test.core.serialization COMMAND test.core.serialization)