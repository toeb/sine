#pragma once

#include <lua/src/lua.hpp>
  
// returns true if table had to be created
bool requireGlobalTable(lua_State *L, const char * name);
// returns true if table had to be created
bool requireTableField(lua_State * L, const char * name);
