#include <core.testing.h>

#include <core.reflection.h>
#include <fstream>
#include <scripting.lua.h>
#include <map>
#include <lua/src/lua.hpp>
#include <scripting.lua/LuaHelpers.h>
using namespace std;
using namespace nspace;


class UserDataStruct : public PropertyChangingObject{
  REFLECTABLE_OBJECT(UserDataStruct);
public:

  PROPERTY(int, Value1){}
  PROPERTY(std::string, Value2){}

};

class UserDataStruct2 : public PropertyChangingObject{
  REFLECTABLE_OBJECT(UserDataStruct2);
public:

  PROPERTY(bool, Value1){}
  PROPERTY(std::string, Value2){}
  ACTION(Lol){cout << "Lolinger"<<getValue1()<<getValue2()<<endl;}

}astruct;

UNITTEST(requireGlobalTable){
  LuaVirtualMachine vm;
  int before = lua_gettop(vm.state());
  auto result = requireGlobalTable(vm.state(),"globalname");
  CHECK(result);

  int after=lua_gettop(vm.state());
  result = requireGlobalTable(vm.state(),"globalname");
  CHECK((before+1)==after);// requireGlobalTable leaves the table on the stack
  lua_pop(vm.state(),1);//remove
  CHECK(!result);
  after=lua_gettop(vm.state());
  CHECK((before+1)==after);
}


UNITTEST(requireTableField){
  LuaVirtualMachine vm;
  requireGlobalTable(vm.state(),"globalname");
  int before = lua_gettop(vm.state());  
  bool created = requireTableField(vm.state(),"somename");
  int after=lua_gettop(vm.state());
  CHECK(created);
  CHECK(before+1==after);// requireTablefield leaves table on top of stack
  lua_pop(vm.state(),1);
  created = requireTableField(vm.state(),"somename");
  CHECK(!created);
  CHECK(before+1==after);
}
UNITTEST(LuaUserData){
  UserDataStruct uut;
  uut.setValue1(32);
  uut.setValue2("asdldigger");
  LuaVirtualMachine vm;
  vm.registerType(typeof(UserDataStruct));
  vm.registerType(typeof(UserDataStruct2));
  vm.registerType(typeof(UserDataStruct2));
  auto l = vm.state();
  auto res = vm.loadFile("scripts/lua/sine.lua");
  cout << ""<<endl;
}



UNITTEST(LuaInitialization){
  LuaVirtualMachine vm;
  CHECK(vm.loadString("-- just a comment"));
}

// function to call from lua
int displayLuaFunction(lua_State *l)
{
  // number of input arguments
  int argc = lua_gettop(l);

  // print input arguments
  std::cout << "[C++] Function called from Lua with " << argc 
    << " input arguments" << std::endl;
  for(int i=0; i<argc; i++)
  {
    std::cout << " input argument #" << argc-i << ": "
      << lua_tostring(l, lua_gettop(l)) << std::endl;
    lua_pop(l, 1);
  }

  // push to the stack the multiple return values
  std::cout << "[C++] Returning some values" << std::endl;
  lua_pushnumber(l, 12);
  lua_pushstring(l, "See you space cowboy");

  // number of return values
  return 2;
}

/**
* \brief This test calls a c function from lua
*        code taken from http://blog.acamara.es/2012/08/19/calling-c-functions-from-lua-5-2/
*/
UNITTEST(LuaScriptCallCppFunction){
  stringstream script;                                                                                                
  script << "-- call the registered C-function                                                      " <<endl;
  script << "io.write('[Lua] Calling the C functionn')                                              " <<endl;
  script << "a,b = displayLuaFunction(12, 3.141592, 'hola')                                         " <<endl;
  script << "                                                                                       " <<endl;
  script << "-- print the return values                                                             " <<endl;
  script << "io.write('[Lua] The C function returned <' .. a .. '> and <' .. b .. '>n')             " <<endl;


  // new Lua state
  std::cout << "[C++] Starting Lua state" << std::endl;
  lua_State *lua_state = luaL_newstate();

  // load Lua libraries
  std::cout << "[C++] Loading Lua libraries" << std::endl;
  static const luaL_Reg lualibs[] = 
  {
    {"base", luaopen_base},
    {"io", luaopen_io},
    {NULL, NULL}
  };
  const luaL_Reg *lib = lualibs;
  for(; lib->func != NULL; lib++)
  {
    std::cout << " loading '" << lib->name << "'" << std::endl;
    luaL_requiref(lua_state, lib->name, lib->func, 1);
    lua_settop(lua_state, 0);
  }

  // push the C++ function to be called from Lua
  std::cout << "[C++] Pushing the C++ function" << std::endl;
  lua_pushcfunction(lua_state, displayLuaFunction);
  lua_setglobal(lua_state, "displayLuaFunction");

  // load the script
  std::cout << "[C++] Loading the Lua script" << std::endl;
  //int status = luaL_loadfile(lua_state, "parrotscript.lua");
  int status = luaL_loadstring(lua_state, script.str().c_str());
  std::cout << " return: " << status << std::endl;

  // run the script with the given arguments
  std::cout << "[C++] Running script" << std::endl;
  int result = 0;
  if(status == LUA_OK)
  {
    result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
  }
  else
  {
    std::cout << " Could not load the script." << std::endl;
    FAIL("could not load script");
  }

  // close the Lua state
  std::cout << "[C++] Closing the Lua state" << std::endl;

}

/**
* \brief Tests a script which returns the arguments passed to it.
*        Taken from http://blog.acamara.es/2012/08/15/passing-variables-from-lua-5-2-to-c-and-vice-versa/
*
*/
UNITTEST(luaScriptArgumentPassingAndReturnValues){

  stringstream script;

  script <<" -- print the arguments passed from C                                          "<<endl;
  script <<" io.write(\"[Lua] These args were passed into the script from C\\n\")          "<<endl;
  script <<" for i=1,#arg do                                                               "<<endl;
  script <<"     print(\"      \", i, arg[i])                                              "<<endl;
  script <<" end                                                                           "<<endl;
  script <<" -- return a value of different Lua types (boolean, table, numeric, string)    "<<endl;
  script <<" io.write(\"[Lua] Script returning data back to C\\n\")                        "<<endl;
  script <<"                                                                               "<<endl;
  script <<" -- create the table                                                           "<<endl;
  script <<" local temp = {}                                                               "<<endl;
  script <<" temp[1]=9                                                                     "<<endl;
  script <<" temp[2]=\"See you space cowboy!\"                                             "<<endl;
  script <<"                                                                               "<<endl;
  script <<" return true,temp,21,\"I am a mushroom\"                                       "<<endl;

  // new Lua state
  std::cout << "[C++] Starting Lua state" << std::endl;
  lua_State *lua_state = luaL_newstate();

  // load Lua libraries
  std::cout << "[C++] Loading Lua libraries" << std::endl;
  static const luaL_Reg lualibs[] = 
  {
    {"base", luaopen_base},
    {"io", luaopen_io},
    {NULL, NULL}
  };
  const luaL_Reg *lib = lualibs;
  for(; lib->func != NULL; lib++)
  {
    std::cout << " loading '" << lib->name << "'" << std::endl;
    luaL_requiref(lua_state, lib->name, lib->func, 1);
    lua_settop(lua_state, 0);
  }

  // start the arg table in Lua
  std::cout << "[C++] Creating the arg table" << std::endl;
  lua_createtable(lua_state, 2, 0);
  lua_pushnumber(lua_state, 1);
  lua_pushnumber(lua_state, 49);
  lua_settable(lua_state, -3);
  lua_pushnumber(lua_state, 2);
  lua_pushstring(lua_state, "Life is a beach");
  lua_settable(lua_state, -3);
  lua_setglobal(lua_state, "arg");

  // load the script
  std::cout << "[C++] Loading the Lua script" << std::endl;
  //int status = luaL_loadfile(lua_state, "parrotscript.lua");
  int status = luaL_loadstring(lua_state, script.str().c_str());
  std::cout << " return: " << status << std::endl;

  // run the script with the given arguments
  std::cout << "[C++] Running script" << std::endl;
  int result = 0;
  if(status == LUA_OK)
  {
    result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
  }
  else
  {
    std::cout << " Could not load the script." << std::endl;
    FAIL("Could not load script");
  }

  // print the values returned from the script
  std::cout << "[C++] Values returned from the script:" << std::endl;
  std::stringstream str_buf;
  while(lua_gettop(lua_state))
  {
    str_buf.str(std::string());
    str_buf << " ";
    switch(lua_type(lua_state, lua_gettop(lua_state)))
    {
    case LUA_TNUMBER:
      str_buf << "script returned the number: "
        << lua_tonumber(lua_state, lua_gettop(lua_state));
      break;
    case LUA_TTABLE:
      str_buf << "script returned a table";
      break;
    case LUA_TSTRING:
      str_buf << "script returned the string: "
        << lua_tostring(lua_state, lua_gettop(lua_state));
      break;
    case LUA_TBOOLEAN:
      str_buf << "script returned the boolean: "
        << lua_toboolean(lua_state, lua_gettop(lua_state));
      break;
    default:
      str_buf << "script returned an unknown-type value";
    }
    lua_pop(lua_state, 1);
    std::cout << str_buf.str() << std::endl;
  }

  // close the Lua state
  std::cout << "[C++] Closing the Lua state" << std::endl;

}

/**
* \brief Minimal lua script run test from http://blog.acamara.es/2012/08/14/running-a-lua-5-2-script-from-c/
*
*/
UNITTEST(luaScriptMinimal){
  // create new Lua state
  lua_State *lua_state;
  lua_state = luaL_newstate();

  // load Lua libraries
  static const luaL_Reg lualibs[] =
  {
    { "base", luaopen_base },
    { NULL, NULL}
  };

  const luaL_Reg *lib = lualibs;
  for(; lib->func != NULL; lib++)
  {
    lib->func(lua_state);
    lua_settop(lua_state, 0);
  }

  // run the Lua script
  //luaL_dostring(lua_state, "print('Hello World!')");
  luaL_loadstring(lua_state,"print('Hello World!')");



  // close the Lua state
  lua_close(lua_state);
}