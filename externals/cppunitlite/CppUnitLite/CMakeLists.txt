set(source
Failure.h
Failure.cpp
SimpleString.h
SimpleString.cpp
Test.h
Test.cpp
TestRegistry.h
TestRegistry.cpp
TestResult.h
TestResult.cpp
TestRegistry.h

)
source_group("" FILES ${source})
add_library(cppunitlite ${source} CMakeLists.txt)
project_folder(${dslibExternalsProjectFolder} cppunitlite)
