

find_package(V8)




set(source 
 Javascript.h
 Javascript.cpp
 ../include/scripting.javascript.h
)


set(V8_LIBRARY_PATH 
#${externalsDirectory}/v8/build/Debug/lib/preparser_lib.lib 
${externalsDirectory}/v8/build/Debug/lib/v8_base.lib 
${externalsDirectory}/v8/build/Debug/lib/v8_snapshot.lib 
#${externalsDirectory}/v8/build/Debug/lib/v8_nosnapshot.lib 

)
add_library(scripting.javascript ${source} CMakeLists.txt)
target_link_libraries(scripting.javascript scripting ${V8_LIBRARY_PATH} ws2_32)