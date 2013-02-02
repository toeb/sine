#include <core.testing.h>

#include <core.reflection.h>
#include <fstream>
#include <scripting.lua.h>
#include <map>
using namespace std;
using namespace nspace;
class SampleClass : public nspace::PropertyChangingObject{
  REFLECTABLE_OBJECT(SampleClass);

  PROPERTY(int, Value1){}
  PROPERTY(std::string, Value2){}

  OBJECTPOINTERPROPERTY(SampleClass, Parent){}

};


class VirtualScriptMachine : public virtual Log{

public:
  virtual void registerFunction(){}
  virtual void registerType(const Type * type){}
  virtual void registerObject(){}
  virtual void callFunction(){}
  virtual void get(){}

  virtual bool loadStream(std::istream & stream){
    logError("Not implemented");
    return false;
  }
  bool loadString(const std::string & script){
    stringstream stream (script);
    return loadStream(stream);
  }
  bool loadFile(const std::string & filename){
    ifstream stream(filename,fstream::in );

    if(!stream.good()){
      logError("could not load file " << filename);
      return false;
    }
    auto result = loadStream(stream);
    stream.close();
    return result;
  }

};
//http://www.codeproject.com/Articles/11508/Integrating-Lua-into-C
// http://blog.acamara.es/2012/08/14/running-a-lua-5-2-script-from-c/
namespace nspace{
  META(luaL_Reg);
}
/*
SERIALIZERS(luaL_Reg,{
stream << value->name;
},{

});
template<>
class Comparator<luaL_Reg,luaL_Reg>{

public:
static inline void operation(bool & equal, const luaL_Reg a,const luaL_Reg b){
equal =strcmp(a.name,b.name)!=0;
}
};*/



class LuaVirtualMachine : public VirtualScriptMachine{
  REFLECTABLE_OBJECT(LuaVirtualMachine);
  map<std::string,std::function<int(void)> > _functionTable;
  map<std::string,std::function<void(void)> > _scriptFunctions;


  PROPERTYSET(luaL_Reg*,Libraries,{
    loadLibrary(*item);
  },{

  });




private:
  bool loadLibrary(const luaL_Reg & lib){
    logInfo("loading lua library: "<<lib.name);
    luaL_requiref(_state,lib.name,lib.func,1);
    lua_settop(_state, 0);
    return true;

  }
  lua_State * _state;
public:
  lua_State * state(){
    return _state;
  }
  LuaVirtualMachine(){

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
  static int luaPropertySetter(lua_State * state){
    return 0;
  }
  static int luaPropertyGetter(lua_State* state){
    return 0;
  }
  static int luaConstructor(lua_State* state){
    return 0;
  }
  static int luaDestructor(lua_State* state){
    return 0;
  }

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

  void * checkObject(lua_State * L, int index){
    void * result = 0;
    luaL_checktype(L,index,LUA_TTABLE);
    lua_getfield(L, index, "__type");
    void * type = luaL_checkudata(L,index,"Type");
    lua_getfield(L, index, "__self");
    //result = luaL_checkudata(L,index,
  }

  void registerType(const Type * type);

  ~LuaVirtualMachine(){

    // close the Lua state
    lua_close(_state);
    logInfo("closing lua vm");


    Libraries().foreachElement([](luaL_Reg* lib){
      delete lib;
    });
    Libraries().clear();
  }


  void registerFunction(const std::string & name, std::function<int(void)> f){
    _functionTable[name] = f;
  }

  void callFunction(const std::string & name){
    auto it = _scriptFunctions.find(name);
    if(it==_scriptFunctions.end())return; //function not found
    it->second();
  }
  bool loadStream(istream & stream){
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

  void registerGlobalLuaFunction(const std::string & name, lua_CFunction func){
    lua_pushcfunction(_state,func);
    lua_setglobal(_state, name.c_str());
  }

};

int testFunction(){
  std::cout << "lol"<<std::endl;
  return 4;
}

struct ScriptObject{
  void * object;
  const Type * type;
};


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


  lua_getfield(L,1,"__self");
  void * objectdata = lua_touserdata(L,-1);
  

  type->getMethodInfo("Lol")->call((Object*)objectdata);
  

  return 0;
}
void LuaVirtualMachine::registerType(const Type* type){
  logInfo("registering type:"<<type->getName());
  string stdname = type->getName();
  const char * name = stdname.c_str();
  luaL_getmetatable(_state,name);
  bool metatableFound = lua_istable(_state,-1);
  if(metatableFound){
    logError("type '"<<name<<"' already registered");
    return;
  }
  luaL_newmetatable(_state,name);

  //lua_newtable(_state);
  lua_pushstring(_state,name);
  lua_setfield(_state,-2,"__typename");
  //const Type ** luatype = (const Type **)lua_newuserdata(_state,sizeof(const Type*));
  //  *luatype = type;
  lua_pushlightuserdata(_state,const_cast<void*>((const void*)type));
  lua_setfield(_state,-2,"__type");


  for(auto member : type->Members().elements()){    
    if(member->getType()==*typeof(MethodInfo)){      
      lua_pushcfunction(_state, luaCallAction);
      lua_setfield(_state,-2,member->getName().c_str());
    }else if(dynamic_cast<const PropertyInfo*>(member)){    
      lua_pushcfunction(_state, luaGetProperty);
      lua_setfield(_state,-2,DS_INLINE_STRING("get"<<member->getName()).c_str());
      
      lua_pushcfunction(_state, luaSetProperty);
      lua_setfield(_state,-2,DS_INLINE_STRING("set"<<member->getName()).c_str());
      
    }
   }
  lua_pushvalue(_state,-1);
  lua_setfield(_state,-1,"__index");

  //lua_setglobal(_state,"thetable");
  lua_newtable(_state);
  lua_setglobal(_state,"object1");
  
  lua_getglobal(_state,"object1");
  luaL_getmetatable(_state, name);
  lua_setmetatable(_state,-2);

  void** obj = (void**)lua_newuserdata(_state,sizeof(void*));
  *obj = type->createInstance();
  lua_setfield(_state,-2,"__self");


/*
  lua_getglobal(_state,"object1");
  luaL_getmetatable(_state,name);
  lua_setfield(_state,-2,"__index");
  lua_setglobal(_state,"object1");*/
  /*
  //luaL_setmetatable(_state, type->getName().c_str());
  lua_getglobal(_state, "types");
  if(!lua_istable(_state,-1)){
    lua_newtable(_state);
    lua_setglobal(_state,"types");      
  }
  lua_getglobal(_state, "types");
  auto table = lua_istable(_state,-1);
  const Type ** luatype = (const Type **)lua_newuserdata(_state,sizeof(const Type*));
  *luatype = type;
  lua_setfield(_state,-2,type->getName().c_str());*/
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

struct LuaFunctionWrapper{

};

UNITTEST(LuaCFunctionTranslation){


  std::function<tuple<int,std::string,float> (int, int, std::string, float)> fuu=[](int a, int b, std::string c, float d){return make_tuple(a+1,c,d-3);};
  auto val = fuu(2,3,"asd",232.2f);


  FAIL("Not implemented");

}


bool wasCalled = false;
int testLuaFunction(lua_State * state){
  wasCalled = true;
  return 0;
}

UNITTEST(LuaCFunction){
  LuaVirtualMachine vm;
  wasCalled = false;
  vm.registerGlobalLuaFunction("fuu", &testLuaFunction);

  CHECK(!wasCalled);
  vm.loadString("fuu()");
  CHECK(wasCalled);
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