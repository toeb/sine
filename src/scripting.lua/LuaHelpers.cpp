#include "LuaHelpers.h"


using namespace std;


// returns true if table had to be created
bool ::requireGlobalTable(lua_State *L, const char * name){

  lua_getglobal(L,name);
  if(!lua_istable(L,-1)){
    lua_pop(L,1);
    lua_newtable(L);
    lua_setglobal(L,name);
    lua_getglobal(L,name);
    return true;
  }
  return false;

}
// returns true if table had to be created
bool ::requireTableField(lua_State * L, const char * name){
  lua_getfield(L,-1,name);
  if(!lua_istable(L,-1)){
    // remove nil or whatever non table value from stack
    lua_pop(L,1);
    // create table
    lua_newtable(L);
    lua_setfield(L,-2,name);
    lua_getfield(L,-1,name);
    return true;
  }
  return false;
}
