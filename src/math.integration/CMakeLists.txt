set(source
 Integrator.h
 Integrator.cpp
 )
 source_group("" FILES ${source})
 add_library(math.integration ${source} CMakeLists.txt)
 target_link_libraries(math.integration math.matrix)