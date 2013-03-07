#pragma once


#include <scripting.h>
#include <core.logging.h>
struct lua_State;
struct luaL_Reg;
namespace nspace{
  
  class ScriptObject : public Object{
    reflect_type(ScriptObject);

  public:
    void toString(std::ostream & out)const{
      //  getObjectType()->objectToString(getObjectPointer().get(),out);
    }
    ScriptObject():_ObjectType(0){}
    typedef std::shared_ptr<void> basic_property(ObjectPointer);
    typedef const Type * basic_property(ObjectType);
    template<typename T> std::shared_ptr<T> object(){return std::static_pointer_cast<T>(getObjectPointer());}
  };


  class LuaVirtualMachine : public VirtualScriptMachine{
    REFLECTABLE_OBJECT(LuaVirtualMachine);
    PROPERTYSET(luaL_Reg*,Libraries,{loadLibrary(*item);},{});
    
  private:
    bool loadLibrary(const luaL_Reg & lib);
    lua_State * _state;
  public:
    lua_State * state();

    int stackSize();

    LuaVirtualMachine();

    bool registerType(const Type * type);
    bool registerObject(Object * object);
    bool registerObject(ScriptObject * object);

    ~LuaVirtualMachine();
    bool loadStream(std::istream & stream);


    void scriptObjectConstructed(ScriptObject & object);
    void scriptObjectDestroyed(ScriptObject & object);
  };

}

/*
/*
void registerFunction(const std::string & name, std::function<int(void)> f){
_functionTable[name] = f;
}*/
/*
void callFunction(const std::string & name){
auto it = _scriptFunctions.find(name);
if(it==_scriptFunctions.end())return; //function not found
it->second();
}*/


/*
void registerGlobalLuaFunction(const std::string & name, lua_CFunction func){
lua_pushcfunction(_state,func);
lua_setglobal(_state, name.c_str());
}*/

/*
static int newObject(lua_State* L){
// number of args
int n = lua_gettop(L);

if(n!=2)return luaL_error(L,"Got %d arguments expected 2 : (object, type)",n);

luaL_checktype(L,1,LUA_TTABLE);

luaL_checktype(L,2,LUA_TUSERDATA);



const Type * type = (const Type * )  lua_touserdata(L,2);
if(!type){
return luaL_error(L,"passed type is not a legal const Type * pointer");
}

// create  atable
lua_newtable(L);

// set metatable
lua_pushvalue(L,1);
lua_setmetatable(L,-2);

//
lua_pushvalue(L,1);
lua_setfield(L,1,"__index");


//luaL_checkudata(L,2,
void ** object = (void**)lua_newuserdata(L,sizeof(void*));

luaL_getmetatable(L,type->getName().c_str());


*object = type->createInstance();
if(!*object){
return luaL_error(L,"C++ Type '%s' cannot be instanciated",type->getName());
}

lua_setmetatable(L,-2);
lua_setfield(L,-2,"__self");

lua_setuservalue(L,-2);
lua_setfield(L,-2,"__type");
return 1;

}
*/
/*
void test(){
static const luaL_Reg gSpriteFuncs[] = {
// Creation
{"new", newSprite},
{"position", position},
{"nextPosition", nextPosition},    
{"setPosition", setPosition},  
{"render", render},      
{"update", update},          
{"collision", collision},   
{"move", move},    
{"accelerate", accelerate},      
{"rotate", rotate},  
{NULL, NULL}
};

}*/
/*
void * checkObject(lua_State * L, int index){
void * result = 0;
luaL_checktype(L,index,LUA_TTABLE);
lua_getfield(L, index, "__type");
void * type = luaL_checkudata(L,index,"Type");
lua_getfield(L, index, "__self");
//result = luaL_checkudata(L,index,
}*/