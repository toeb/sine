#pragma once

#include <lua/src/lua.hpp>
#include <config.h>

namespace nspace{
// returns true if table had to be created
bool requireGlobalTable(lua_State *L, const char * name);
// returns true if table had to be created
bool requireTableField(lua_State * L, const char * name);

template<typename T> T* luaCheckUserData(lua_State* L){
  if(!lua_islightuserdata(L,-1))return 0;
  T * result = 0;
  result = static_cast<T*>(lua_touserdata(L,-1));
  lua_pop(L,1);
  return result;
}
template<typename T> T* luaUserDataField(lua_State* L, int idx, const char* name){
  lua_getfield(L,idx,name);
  return luaCheckUserData<T>(L);
}

}
