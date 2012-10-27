set(source
 Module.h
 Module.cpp
 Hub.h
 Hub.cpp 
 ModuleBase.h
 ModuleBase.cpp 
 HubObject.h
 HubObject.cpp 
 CompositeHubObject.h
 CompositeHubObject.cpp 
 ../include/core.hub.h
 )
 
 source_group("" FILES ${source})
 
 add_library(core.hub ${source} CMakeLists.txt)
 
 target_link_libraries(core.hub core core.logging)
