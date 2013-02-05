#include "Lua.h"

using namespace nspace;
using namespace std;

#include <lua/src/lua.hpp>
#include <scripting.lua/LuaHelpers.h>
#include <core.preprocessor.h>

void lua_pushstring(lua_State * L, const std::string& str){
  lua_pushstring(L,str.c_str());
}
LuaVirtualMachine * luaGetVM(lua_State * L);
int luaCallClass(lua_State*L){return 0;}
int luaClassToString(lua_State*L){return 0;}
int luaCallMethod(lua_State*L){return 0;}
int luaSetProperty(lua_State*L){return 0;}
int luaGetProperty(lua_State*L){return 0;}
int luaConstructor(lua_State*L);
int luaToString(lua_State*L){return 0;}
int luaTypeToString(lua_State*L){return 0;}
int luaMemberMethod(lua_State*L);

int luaClassDestructor(lua_State*L){return 0;}
int luaObjectDestructor(lua_State*L){

  auto n = lua_gettop(L);
  if(n!=1){
    return 0;
  }

  auto object = luaUserDataField<ScriptObject>(L,1,"cscriptobject");
  if(!object){
    return 0;
  }

  luaGetVM(L)->deletingScriptObject(*object);
  delete object;
  object = 0;
  return 0;
}
int luaObjectToString(lua_State*L){
  auto n = lua_gettop(L);
  if(n!=1)return 0;

  auto object = luaUserDataField<ScriptObject>(L,1,"cscriptobject");
  if(object){
    string s = object->getObjectType()->objectToString(object->getObjectPointer().get());
    lua_pushstring(L,s);
  }else{
    lua_pushstring(L,"<no to string method>");
  }
  return 0;
}


bool createType(lua_State*L,const Type*type);
bool createPropertyMetaTable(lua_State* L){return false;}
bool createMethodMetaTable(lua_State* L){return false;}
bool createTypeMetaTable(lua_State * L){return false;}
bool createMemberMetaTable(lua_State*L){return false;}
bool createObjectMetaTable(lua_State*L, const Type * type);


bool createObject(lua_State*L, ScriptObject  object);


void createMethod(lua_State* L, const MemberInfo * method);
void createProperty(lua_State* L, const PropertyInfo * prop);
void createMember(lua_State*L, const MemberInfo* member);
bool createClass(lua_State*L,const Type *type);
#define DS_LUA_VM_FIELD_NAME "vm"
void luaSetVM(lua_State* L, LuaVirtualMachine* vm){  
  lua_pushlightuserdata(L,vm);
  lua_setglobal(L,DS_LUA_VM_FIELD_NAME);
}

LuaVirtualMachine * luaGetVM(lua_State * L){
  lua_getglobal(L,DS_LUA_VM_FIELD_NAME);
  LuaVirtualMachine*  result = 0;
  if(lua_islightuserdata(L,-1)){
    result = (LuaVirtualMachine*)lua_touserdata(L,-1);
  }
  lua_pop(L,1);
  return result;
}

bool createObject(lua_State*L, ScriptObject object){
  return false;
}

int luaMemberMethod(lua_State*L){
  auto n = lua_gettop(L);
  if(n<1){
    return 0;
  }
  auto member = luaUserDataField<const MemberInfo>(L,1,"cmemberinfo");
  auto object = luaUserDataField<ScriptObject>(L,1,"cscriptobject");
  if(!member){
    return 0;
  }
  if(!object){
    return 0;
  }
  auto method = dynamic_cast<const MethodInfo*>(member);
  if(method){
    method->unsafeCall(object->getObjectPointer().get());
    return 0;
  }
  auto prop = dynamic_cast<const PropertyInfo*>(member);
  if(prop){
    prop->setValue(0,0);
    prop->getValue(0,0);

    return 0;
  }
}
int luaConstructor(lua_State*L){  
  int n= lua_gettop(L);

  if(n < 1){
    return luaL_error(L,"to few args in constructor.  expecting class");
  }


  if(!lua_istable(L,1)){
    return luaL_error(L,"first argument is not  a table");
  }


  // extract type
  const Type * type =  luaUserDataField<const Type>(L,1,"ctype");
  if(!type)return luaL_error(L,"class table does not contain type *");

  lua_newtable(L);
  // create user data
  ScriptObject * object = new ScriptObject();

  object->setObjectType(type);  
  object->setObjectPointer(type->createInstance());

  luaGetVM(L)->scriptObjectCreated(*object);

  lua_pushlightuserdata(L,object);
  lua_setfield(L,-2,"cscriptobject");


  string classname = type->getName();

  // metatable for object

  lua_newtable(L);

  lua_pushcfunction(L,luaObjectToString);
  lua_setfield(L,-2,"__tostring");

  lua_pushcfunction(L,luaObjectDestructor);
  lua_setfield(L,-2,"__gc");

  //member table
  lua_newtable(L);
  type->Members().foreachElement([L,object](const MemberInfo* member){
    string stdname= member->getName();
    auto name = stdname.c_str();

    // table for member object
    lua_newtable(L);


    // set object's member object pointer
    lua_pushlightuserdata(L,const_cast<MemberInfo*>(member));      
    lua_setfield(L,-2,"cmemberinfo");
    lua_pushlightuserdata(L,object);
    lua_setfield(L,-2,"cscriptobject");
    // new metatable 
    lua_newtable(L);
    lua_pushcfunction(L,luaMemberMethod);
    lua_setfield(L,-2,"__call");
    //set method objects metatable
    lua_setmetatable(L,-2);

    lua_setfield(L,-2,name);
  });

  lua_setfield(L,-2,"__index");

  lua_setmetatable(L,-2);





  return 1;
}


bool createClass(lua_State*L,const Type *type){
  // table already on stack

  string name = type->getName();

  lua_pushcfunction(L,luaToString);
  lua_setfield(L,-2,"__tostring");

  lua_pushcfunction(L,luaCallClass);
  lua_setfield(L,-2,"__call");

  lua_pushcfunction(L,luaClassDestructor);
  lua_setfield(L,-2,"__gc");


  if(type->getIsConstructible()){
    lua_pushcfunction(L,luaConstructor);
    lua_setfield(L,-2,"new");
  }

  lua_pushlightuserdata(L,static_cast<void*>(const_cast<Type*>(type)));
  lua_setfield(L,-2,"ctype");


  type->Members().foreachElement([L](const MemberInfo* member){
    string name = member->getName();
    requireTableField(L,name.c_str());
    createMember(L,member);
    lua_pop(L,1);
  });


  luaL_setmetatable(L,name.c_str());

  return true;
}

void requireClass(lua_State*L,const Type* type){
  std::string stdName = type->getName();
  const char * name = stdName.c_str();
  requireGlobalTable(L,"Class");



  if(requireTableField(L,name)){
    createClass(L,type);    

    return;
  }
}


void createProperty(lua_State* L, const PropertyInfo * prop){  
  // table already on stack


  lua_pushlightuserdata(L,static_cast<void*>(const_cast<PropertyInfo*>(prop)));
  lua_setfield(L,-2,"_cproperty");

  lua_pushstring(L,prop->getName());
  lua_setfield(L,-2,"name");


  if(prop->getHasGetter()){
    lua_pushcfunction(L,luaGetProperty);
    lua_setfield(L,-2,"get");
  }
  if(prop->getHasSetter()){
    lua_pushcfunction(L,luaSetProperty);
    lua_setfield(L,-2,"set");
  } 

}
void createMethod(lua_State* L, const MemberInfo * method){
  // table is already on top of stack
  lua_pushstring(L,method->getName());
  lua_setfield(L,-2,"name");


  lua_pushcfunction(L,luaCallMethod);
  lua_setfield(L,-2,"call");


}

bool LuaVirtualMachine::registerObject(Object * object){return false;}
bool LuaVirtualMachine::registerObject(ScriptObject * object){return false;}


bool createObject(lua_State*L, ScriptObject* scriptObject){
  auto type = scriptObject->getObjectType();
  auto object = scriptObject->getObjectPointer();

  //logInfo("Creating object");

  lua_newtable(L);

  requireClass(L,type);
  lua_setmetatable(L,-2);

  lua_pushlightuserdata(L,scriptObject);
  lua_setfield(L,-2,"__cobject");


  return true;
}

bool LuaVirtualMachine::registerType(const Type* type){
  auto L = _state;
  logInfo("registering type:"<<type->getName());

  requireClass(L,type);
  lua_pop(L,1);

  return true;
}






// creates the metatable for type t and leaves it on the stack
bool createType(lua_State * L, const Type * type){
  std::string stdName = type->getName();
  const char*  name = stdName.c_str();

  requireGlobalTable(L,"Class");

  // create metatable (if it already exists return false)
  if(!requireTableField(L,name)){
    return false;
  }
  // set metatable for new type
  luaL_getmetatable(L,"Type");
  lua_setmetatable(L,-2);

  // assign the c object pointer
  lua_pushlightuserdata(L,const_cast<void*>(static_cast<const void*>(type)));
  lua_setfield(L,-2,"__ctype");

  // create parent types table
  lua_newtable(L);
  type->foreachPredecessor([L](const Type * type){
    //createType(L,type);
    //string name = type->getName();
    // luaL_getmetatable(L,name.c_str());
    //  lua_setfield(L,-2,name.c_str());
  });
  lua_setfield(L,-2,"superclasses");


  type->Members().foreachElement([L](const MemberInfo * member){
    createMember(L,member);  
  });



  lua_pop(L,1);// superclasses -> type
  lua_pop(L,1);// Class -> 0


  return true;
}




void LuaVirtualMachine::scriptObjectCreated(ScriptObject & object){
  logInfo("lua created object "<<object);
}
void LuaVirtualMachine::deletingScriptObject(ScriptObject & object){
  logInfo("lua deleting object "<<object);
}



//------------------------------------------------------------------------------------------------------------------
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

  luaSetVM(_state,this);

  /*
  createTypeMetaTable(_state);
  createMemberMetaTable(_state);
  createMethodMetaTable(_state);
  createPropertyMetaTable(_state);
  */
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



void createMember(lua_State*L,const MemberInfo * member){
  if(dynamic_cast<const PropertyInfo*>(member)){
    createProperty(L,dynamic_cast<const PropertyInfo*>(member));
  }else if(dynamic_cast<const MethodInfo*>(member)){
    createMethod(L,dynamic_cast<const MethodInfo*>(member));
  }
}
