set(source
 UnitTest.h
 UnitTest.cpp
 UnitTestRunner.h
 UnitTestRunner.cpp 
 PerformanceTest.h
 PerformanceTest.cpp 
 TestResult.h
 TestResult.cpp 
 macros.h
 ../include/core.testing.h
 CMakeLists.txt
 )
 source_group("" FILES ${source})
 
 add_library(core.testing ${source})
 target_link_libraries(core.testing core core.task)

