set(source 
 Lua.h
 Lua.cpp
 LuaHelpers.h
 LuaHelpers.cpp
 ../include/scripting.lua.h
)

add_library(scripting.lua ${source} CMakeLists.txt)
target_link_libraries(scripting.lua scripting lua)