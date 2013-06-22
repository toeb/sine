set(source
 Injector.h
 Injector.cpp
 ../include/core.injection.h
 )
 
 source_group("" FILES ${source})
 
 add_library(core.injection ${source} CMakeLists.txt)
 
 target_link_libraries(core.injection core core.reflection)
