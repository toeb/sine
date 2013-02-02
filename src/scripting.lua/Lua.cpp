#include "Lua.h"

using namespace nspace;
using namespace std;

#include <lua/src/lua.hpp>
#include <scripting.lua/LuaHelpers.h>
#include <core.preprocessor.h>


bool LuaVirtualMachine::loadLibrary(const luaL_Reg & lib){
  logInfo("loading lua library: "<<lib.name);
  luaL_requiref(_state,lib.name,lib.func,1);
  lua_settop(_state, 0);
  return true;
}
lua_State * LuaVirtualMachine::state(){
  return _state;
}

int LuaVirtualMachine::stackSize(){
  return lua_gettop(_state);
}

LuaVirtualMachine::LuaVirtualMachine(){

  // create new state
  logInfo("creating lua state");
  _state = luaL_newstate();    

  // add default libraries
  luaL_Reg base = {"base",luaopen_base};
  luaL_Reg io = {"io",luaopen_io};
  luaL_Reg math = {"file",luaopen_math};
  luaL_Reg os = {"os",luaopen_os};
  luaL_Reg string = {"string", luaopen_string};
  Libraries()|=new luaL_Reg(base);
  Libraries()|=new luaL_Reg(io);
  Libraries()|=new luaL_Reg(math);
  Libraries()|=new luaL_Reg(os);
  Libraries()|=new luaL_Reg(string);
}



LuaVirtualMachine::~LuaVirtualMachine(){

  // close the Lua state
  lua_close(_state);
  logInfo("closing lua vm");


  Libraries().foreachElement([](luaL_Reg* lib){
    delete lib;
  });
  Libraries().clear();
}
bool LuaVirtualMachine::loadStream(std::istream & stream){
  std::istreambuf_iterator<char> eos;
  std::string script(std::istreambuf_iterator<char>(stream), eos);

  int status = luaL_loadstring(_state, script.c_str());

  if(status!=LUA_OK){
    logError("Could not load script, errorcode:" <<status);
    return false;
  }
  lua_pcall(_state, 0, LUA_MULTRET, 0);

  return true;
}



int luaSetProperty(lua_State * L){
  return 0;
}
int luaGetProperty(lua_State * L){
  lua_pushstring(L,"somereturnvalue");
  return 1;
}

int luaCallAction(lua_State * L){

  int n= lua_gettop(L);
  if(n!=1){
    return luaL_error(L,"action needs to be called on self");
  }

  if(!lua_istable(L,-1)){
    return luaL_error(L,"self must be a table");
  }

  auto fieldFound = luaL_getmetafield(L,-1,"__type");
  void* typedata = lua_touserdata(L,-1);
  auto type= (const Type*)typedata;

  //lua_pop(L,-1);
  /*

  lua_getfield(L,1,"__self");
  void * objectdata = lua_touserdata(L,-1);


  type->getMethodInfo("Lol")->call((Object*)objectdata);

  */
  return 0;
}


const Type * luaGetType(lua_State* L, int index){
  lua_getfield(L,index,"__ctype");
  if(!lua_isuserdata(L,-1))return 0;
  void * ptr = lua_touserdata(L,-1);  
  lua_pop(L,1);
  return static_cast<Type*>(ptr);
}
const Type * luaGetTypeMeta(lua_State* L, int index){
  luaL_getmetafield(L,index,"__ctype");
  if(!lua_isuserdata(L,-1))return 0;
  void * ptr = lua_touserdata(L,-1);  
  lua_pop(L,1);
  return static_cast<Type*>(ptr);
}

void  * luaGetObject(lua_State* L, int index){
  luaL_getmetafield(L,index,"__cobject");
  if(!lua_isuserdata(L,-1))return 0;
  void * ptr=  lua_touserdata(L,-1);
  lua_pop(L,1);
  return ptr;
}
const MemberInfo * luaGetMemberInfo(lua_State*L,int index){

  lua_getfield(L,index,"__memberInfo");
  if(!lua_isuserdata(L,-1))return 0;
  void * ptr = lua_touserdata(L,-1);  
  lua_pop(L,1);
  return static_cast<MemberInfo*>(ptr);
}

int luaDestructor(lua_State * L){
  cout << "destructor called"<<endl;
  return 0;
}
int luaToString(lua_State * L){
  cout << "to string called";
  auto type = luaGetTypeMeta(L,-1);
  auto object = luaGetObject(L,-1);

  lua_pushstring(L, "TOSTRING RETURN VALUE IS NOT YET IMPLEMENTED");
  return 1;
}
int luaInheritanceSolver(lua_State*L){
  cout << "unknown call needs to be resolved"<<endl;
  //t,k
  return 0;
}
int luaConstructor(lua_State* L){
  cout <<"constructor called"<<endl;
  auto n = lua_gettop(L);
  if(n<1)return luaL_error(L,"expected at least one argument");
  auto type = luaGetType(L,1);
  if(!type){
    return luaL_error(L, "expected type object as first argument");
  }
  auto typenameStd = type->getName();
  auto typeName = typenameStd.c_str();
  void * instance = type->createInstance();


  // new object
  lua_newtable(L);

  if(luaL_newmetatable(L,type->getName().c_str())){
    // assign garbage collection function
    lua_pushcfunction(L,luaDestructor);
    lua_setfield(L,-2,"__gc");

    // assign the c object pointer
    lua_pushlightuserdata(L,instance);
    lua_setfield(L,-2,"__cobject");

    // assign the c type pointer
    lua_pushlightuserdata(L,const_cast<void*>(static_cast<const void*>(type)));
    lua_setfield(L,-2,"__ctype");

    // set to string function
    lua_pushcfunction(L,luaToString);
    lua_setfield(L,-2,"__tostring");

    // make metatable immutable
    //  lua_pushnil(L);
    //  lua_setfield(L,-2,"__metatable");

    //inheritance
    lua_pushcfunction(L,luaInheritanceSolver);
    lua_setfield(L,-2,"__index");

    // no new fields allowd
    lua_pushnil(L);
    lua_setfield(L,-2,"__newindex");


  }
  // set object's metattable
  lua_setmetatable(L,-2);

  return 1;
}
void LuaVirtualMachine::registerType(const Type* type){
  logInfo("registering type:"<<type->getName());
  string stdname = type->getName();
  const char * name = stdname.c_str();
  /* luaL_getmetatable(_state,name);
  bool metatableFound = lua_istable(_state,-1);
  if(metatableFound){
  logError("type '"<<name<<"' already registered");
  return;
  }
  lua_pop(_state,1);
  luaL_newmetatable(_state,name);
  lua_pop(_state,1) ;
  */


  requireGlobalTable(_state,"Types");
  requireTableField(_state, name);

  lua_pushcfunction(_state,luaConstructor);
  lua_setfield(_state, -2,"__new");

  lua_pushcfunction(_state,luaDestructor);
  lua_setfield(_state,-2,"__destroy");

  lua_pushstring(_state,name);
  lua_setfield(_state,-2,"__typename");

  //const Type ** luatype = (const Type **)lua_newuserdata(_state,sizeof(const Type*));
  //  *luatype = type;
  lua_pushlightuserdata(_state,const_cast<void*>((const void*)type));
  lua_setfield(_state,-2,"__ctype");


  for(auto member : type->Members().elements()){    
    registerProperty(member);
  }

  lua_pop(_state,1);      
  lua_pop(_state,1);

}
int luaCallMethod(lua_State*L){

  int n= lua_gettop(L);
  if(n < 2){
    return luaL_error(L,"method can needs first argument to be a MethodInfo and the second to be an Object");
  }

  if(!lua_istable(L,1)){
    return luaL_error(L,"self must be a table");
  }

  lua_getfield(L,1,"__memberPointer"); // get typefield of Member object
  auto result = lua_isuserdata(L,-1);
  void * udata=  lua_touserdata(L,-1); // get userdata
  lua_pop(L,1); //--> remove typefield

  const MemberInfo * member = static_cast<MemberInfo*>(static_cast<void*>(udata));

  auto fieldFound = luaL_getmetafield(L,-1,"__type");
  void* typedata = lua_touserdata(L,-1);
  auto type= (const Type*)typedata;


  cout << "muahahaahah";
  return 0;
}

void LuaVirtualMachine::registerProperty(const MemberInfo * member){
  const char * ns = "ds";
  const char * propertyClassName = "Property";
  const Type * type = member->getOwningType();
  auto typeNameStd = type->getName();
  auto typeName = typeNameStd.c_str();
  string memberNameStd = member->getName();
  const char * memberName = memberNameStd.c_str();
  string fullMemberNameStd = DS_INLINE_STRING(type->getName()<<"."<<member->getName());
  const char* fullMemberName =fullMemberNameStd.c_str();
  // global table types
  requireGlobalTable(_state,"Types");

  // type table
  requireTableField(_state,typeName);

  // member table
  requireTableField(_state, memberName);
  void * udata = const_cast<void*>(static_cast<const void*>(member));
  lua_pushlightuserdata(_state,udata);
  lua_setfield(_state,-2,"__memberPointer");

  lua_pushstring(_state,fullMemberName);
  lua_setfield(_state,-2,"fullName");

  string membertype;

  if(dynamic_cast<const PropertyInfo*>(member)){
    membertype = "Property";
    luaL_loadstring(_state, "");
    lua_setfield(_state,-2,"set");
    luaL_loadstring(_state, "");
    lua_setfield(_state,-2,"get");

  }else if(dynamic_cast<const MethodInfo*>(member)){
    membertype = "Method";
    lua_pushcfunction(_state,luaCallMethod);
    lua_setfield(_state,-2,"call");

  }

  lua_pushstring(_state,membertype.c_str());
  lua_setfield(_state,-2,"membertype");

  lua_pop(_state,1);// -> type table
  lua_pop(_state,1);// -> Types table
  lua_pop(_state,1);//->initial state



}