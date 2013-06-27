set(source 
	../include/core.builder.h 
	FluentChainer.h
	FluentChainer.cpp
	FluentFunctionChainer.h
	FluentFunctionChainer.cpp
	Builder.h
	Builder.cpp
	NestedBuilder.h
	NestedBuilder.cpp
	
)

source_group("" FILES ${source})

add_library(core.builder  ${source} CMakeLists.txt)
#target_link_libraries(core.builder)


