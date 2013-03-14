set(source
	tests.cpp
	main.cpp 
)

find_package(zlib)

include_directories(${ZLIB_INCLUDE_DIRS})
 source_group("" FILES ${source})
 add_executable(test.utility.reader.mat ${source} CMakeLists.txt)
 target_link_libraries(test.utility.reader.mat core.testing  core utility.reader.mat)
 project_folder("test" test.utility.reader.mat )

 
 add_test(NAME test.utility.reader.mat COMMAND test.utility.reader.mat)