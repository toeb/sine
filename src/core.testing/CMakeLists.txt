set(source
 UnitTest.h
 UnitTest.cpp
 UnitTestRunner.h
 UnitTestRunner.cpp 
 ../include/core.testing.h
 CMakeLists.txt
 )
 source_group("" FILES ${source})
 
 add_library(core.testing ${source})
 target_link_libraries(core.testing core core.task)

