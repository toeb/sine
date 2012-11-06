set(source 
 Function.h
 Function.cpp
 PiecewiseFunction.h
 Polynom.h
 ../include/math.functions.h 
CMakeLists.txt
 )
 
 source_group("" FILES ${source})
 add_library(math.functions ${source})
 target_link_libraries(math.functions math.matrix math core)
 


