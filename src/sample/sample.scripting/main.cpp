#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>
#include <simulation.dynamics.h>
#include <simulation.utility/DynamicsAlgorithm.h>
#include <fstream>
#include <utility.reader/Reader.h>
#include <utility.reader.trajectory.h>

#include <lua/src/lua.hpp>

using namespace nspace;
using namespace std;



class TestClass : public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(TestClass);
  SUBCLASSOF(Log);

  PROPERTY(int, IntegralValue){}
  PROPERTY(std::string, StringValue){}


};

class ScriptRunner: public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(ScriptRunner);
  SUBCLASSOF(Log);
  OBJECTPOINTERCOLLECTION(Object,Objects,{},{});
public:
  virtual bool runScript(const std::string & script)=0;
};
int my_function(lua_State *L)
{
  int argc = lua_gettop(L);

  std::cerr << "-- my_function() called with " << argc
    << " arguments:" << std::endl;

  for ( int n=1; n<=argc; ++n ) {
    std::cerr << "-- argument " << n << ": "
      << lua_tostring(L, n) << std::endl;
  }

  lua_pushnumber(L, 123); // return value
  return 1; // number of return values
}

class Lua : public virtual ScriptRunner{
  REFLECTABLE_OBJECT(Lua);
  SUBCLASSOF(ScriptRunner);
private:
  lua_State * _state;
public:
  Lua():_state(0){
    _state = luaL_newstate();
    luaopen_io(_state);
    luaopen_base(_state);
    luaopen_table(_state);
    luaopen_string(_state);
    luaopen_math(_state);
  }
  ~Lua(){
    lua_close(_state);
  }


  
  bool runScript(const std::string & script){
    logInfo("loading lua script.  length="<<script.length());
    debugInfo("script: "<<script);
    int error=  luaL_loadstring(_state,script.c_str());
    if(error){
      logWarning("Could not load script! (Error "<<error<<")");
      return false;
    }
    error= lua_pcall(_state,0,LUA_MULTRET,0);
    if(error){
      logWarning("Error executing script (Error "<<error<<")");
      return false;
    }
    return true;
  }



};



void report_errors(lua_State *L, int status){

}






int main(int argc,  char ** argv){  


  
  TestClass object;
  Lua l;
  l.Objects().add(&object);
  l.runScript("for index = 1,5 do\nprint(index)\nend");


}
