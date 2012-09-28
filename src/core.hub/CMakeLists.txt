set(source
 Module.h
 Module.cpp
 Hub.h
 Hub.cpp 
 ModuleBase.h
 ModuleBase.cpp 
 HubObject.h
 HubObject.cpp 
 )
 
 source_group("" FILES ${source})
 
 add_library(core.hub ${source} CMakeLists.txt)
 
 target_link_libraries(core.hub core)
